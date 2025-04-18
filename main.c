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
void render(Game *game, Map *theMap, char map[MAP_SIZE][MAP_SIZE], struct Enemy *enemies);
int quit(Game *game);

int main(int argc, char *argv[]) {
    Game game = init();
    Map theMap;
    
    // move to game object:
    struct Enemy enemies[QUANTITY_ENEMIES];
    initEnemies(enemies);
    char map[MAP_SIZE][MAP_SIZE];

    initMap(&game, &theMap, map); 


    while (1) {
        SDL_PollEvent(&game.event);
        if (game.event.type == SDL_EVENT_QUIT) {
            break;
        }

        game.currentTime = SDL_GetTicks();
        game.timeSinceLastRender = game.currentTime - game.lastRenderTime;
        
        readInputs(&game); 

        if(game.timeSinceLastRender > 1000/FPS) {
           render(&game, &theMap, map, enemies);
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
    unsigned int lastRenderTime = 0;
    unsigned int currentTime = 0;
    unsigned int timeSinceLastRender = 0;
    Game game = {window, renderer, event, rect, map[0], lastRenderTime, currentTime, timeSinceLastRender, player};

    initWindow(&game.window, &game.renderer);
    initPlayer(&game);
    SDL_SetRenderScale(game.renderer, RENDER_SCALE, RENDER_SCALE);

    return game;
}

/**
 * Lets draw!
 */
void render(Game *game, Map *theMap, char map[MAP_SIZE][MAP_SIZE], struct Enemy *enemies) {
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 0);
    SDL_RenderClear(game->renderer);

    drawMap(game, theMap, map); 
    drawPlayer(game, game->renderer, game->rect, &game->player, map);
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
