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

Game init();
void render(Game *game, struct Enemy *enemies);
int quit(Game *game);

int main(int argc, char *argv[]) {
    Game game = init();
        
    struct Enemy enemies[QUANTITY_ENEMIES];
    initEnemies(enemies);

    // stops working when moved into init() for some reason.
    char map[MAP_SIZE][MAP_SIZE];
    game.map = map;
    initMap(&game); 

    while (1) {
        SDL_PollEvent(&game.event);
        if (game.event.type == SDL_EVENT_QUIT) {
            break;
        }

        game.currentTime = SDL_GetTicks();
        game.timeSinceLastRender = game.currentTime - game.lastRenderTime;
        
        readInputs(&game); 

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
    char map[MAP_SIZE][MAP_SIZE];
    Tile tiles[1];
    unsigned int lastRenderTime = 0;
    unsigned int currentTime = 0;
    unsigned int timeSinceLastRender = 0;
    Game game = {
        window, 
        renderer, 
        event, 
        rect,
        lastRenderTime, 
        currentTime, 
        timeSinceLastRender, 
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
    SDL_Quit();
    return 0;
}
