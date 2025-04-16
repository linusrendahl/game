#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_iostream.h>
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_hints.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_error.h"
#include "vendored/SDL_image/include/SDL3_image/SDL_image.h"
//#include <SDL3_image/SDL_image.h>
#include <stdio.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_iostream.h>
#include <stdlib.h>
#include "models.h"
#include "globals.h"
#include "controllers/sdl.h"
#include "controllers/player.h"
#include "controllers/enemy.h"
#include "controllers/map.h"

#define SDL_SOFTWARE_RENDERER   "software"

/** 
 * Add skills: exori, wave, vis hur, ultimate explosion.
 * Collision on enemies.
 * Gain experience / levels / stats.
 * Enemy attacks.
 * Draw sprites.
 * Time to clean up all code / organize / rewrite.
 *
 * Gameplay:
 * - ability to destroy terrain.
 * - procedurally generated maps.
 * - map levels/stairs, portals to other maps.
 * - loot & crafting.
 * - infinite scaling.
 * - coop 5 player teams / matchmaking.
 * - boss fights (telegraphed attacks).
 * - single class, infinite builds (skill tree)
 * - theme of game?
 * - 3d models to 2d sprites / 2d sprites / 3d models (?)
 * 
 * - write tutorial as we go along
 * **/
int main(int argc, char *argv[]) {
    SDL_Window *window; 
    SDL_Renderer *renderer;
    //SDL_Surface *surface;
    //SDL_LoadBMP(const char *file)
    //static SDL_Texture *texture = NULL;
    SDL_Event event;
    SDL_FRect rect = { 0, 0, TILE_SIZE, TILE_SIZE };
    struct Player player;
    struct Enemy enemies[QUANTITY_ENEMIES];
    char map[MAP_SIZE][MAP_SIZE + 1];
    unsigned int lastTime = 0, currentTime;
    unsigned int delta;

    initWindow(&window, &renderer);
    initPlayer(&player);
    initEnemies(enemies);
    initMap(map); 

    char filename[] = "./assets/sprites/character-1.png";
    char floorfile[] = "./assets/sprites/floor.png";
    SDL_Texture *playerTexture;
    SDL_Texture *floorTexture;
    playerTexture = IMG_LoadTexture(renderer, filename);
    floorTexture = IMG_LoadTexture(renderer, floorfile);
    SDL_SetTextureScaleMode(playerTexture, SDL_SCALEMODE_NEAREST);
    SDL_SetTextureScaleMode(floorTexture, SDL_SCALEMODE_NEAREST);
    SDL_SetRenderColorScale(renderer, 1.2f);

    while (1) {
        SDL_PollEvent(&event);
        if (event.type == SDL_EVENT_QUIT) {
            break;
        }

        currentTime = SDL_GetTicks();
        delta = currentTime - lastTime;
        
        readInputs(event, &player); 

        if(delta > 1000/FPS) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);

            drawMap(renderer, map, &player, rect, floorTexture); 
            drawPlayer(renderer, rect, &player, map, playerTexture);
            drawEnemies(renderer, rect, enemies, &player);

            SDL_RenderPresent(renderer);
            lastTime = currentTime;
        }
    }

    SDL_DestroyTexture(playerTexture);
    //SDL_DestroySurface(playerSurface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
