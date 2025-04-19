#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_iostream.h>
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include <SDL3/SDL_gpu.h>
#include "SDL3/SDL_video.h"
#include "vendored/SDL_image/include/SDL3_image/SDL_image.h"
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_iostream.h>
#include "models.h"
#include "globals.h"
#include "controllers/sdl.h"
#include "controllers/player.h"
#include "controllers/enemy.h"
#include "controllers/map.h"
#include "debuggers.h"
#include "controllers/ui.h"
#include "vendored/SDL_ttf/include/SDL3_ttf/SDL_ttf.h"

Game init();
void render(Game *game, struct Enemy *enemies);
int quit(Game *game);

int main(int argc, char *argv[]) {
    Game game = init();
        
    // stops working when moved into init() for some reason.
    // guessing it a problem of scope.
    Tile tiles[MAP_SIZE][MAP_SIZE];
    game.map.tiles = tiles;
    initMap(&game); 

    Enemy enemies[QUANTITY_ENEMIES];
    initEnemies(&game, enemies);
    
    while (1) {
        SDL_PollEvent(&game.event);
        if (game.event.type == SDL_EVENT_QUIT) {
            break;
        }

        game.currentTime = SDL_GetTicks();
        game.timeSinceLastRender = game.currentTime - game.lastRenderTime;
        
        readInputs(&game, enemies); 

        if(game.timeSinceLastRender > 1000/FPS) {
           render(&game, enemies);
        }
    }

    quit(&game); 
    return 0;
}

/**
 * Start the engines
 */
Game init() {
    SDL_Window *window; 
    SDL_Renderer *renderer;
    SDL_Event event;
    Player player;
    SDL_FRect rect = { 0, 0, TILE_SIZE, TILE_SIZE };
    Map map;
    Tile tiles[1];
    unsigned int lastRenderTime = 0;
    unsigned int currentTime = 0;
    unsigned int timeSinceLastRender = 0;
    Game game = {
        window, 
        renderer, 
        event, 
        rect, //do we need a global rect?
        lastRenderTime, // lasttick?
        currentTime, // currenttick?
        timeSinceLastRender, // delta?
        map,
        *tiles, 
        player
    };
    
    initWindow(&game.window, &game.renderer);
    initPlayer(&game); 
    SDL_SetRenderScale(game.renderer, RENDER_SCALE, RENDER_SCALE);

    // initTiles():create
    char floorfile[] = "./assets/sprites/floor.png";
    SDL_Texture *floorTexture;
    floorTexture = IMG_LoadTexture(game.renderer, floorfile);
    SDL_SetTextureScaleMode(floorTexture, SDL_SCALEMODE_NEAREST);
    game.tiles[0].texture = floorTexture;
    game.tiles[0].name = 'B';

    return game;
}

/**
 * Lets draw!
 */
void render(Game *game, struct Enemy *enemies) {
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 0);
    SDL_RenderClear(game->renderer);

    drawMap(game); 
    drawPlayer(game, game->renderer, game->rect, &game->player);
    drawEnemies(game->renderer, game->rect, enemies, &game->player);
    drawUI(game);

    SDL_RenderPresent(game->renderer);
    game->lastRenderTime = game->currentTime;
}

/**
 * Enough games for today
 */
int quit(Game *game) {
    SDL_DestroyTexture(game->player.texture);
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
