#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "models.h"
#include "globals.h"
#include "controllers/sdl.h"
#include "controllers/player.h"
#include "controllers/enemy.h"
#include "controllers/map.h"

/** 
 * Collision on terrain.
 * Queue next player move.
 * Spawn mobs.
 * Attack / use skills.
 * Gain experience / levels / stats.
 * Draw sprites.
 * **/
int main(int argc, char *argv[]) {
    SDL_Window *window; 
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Event event;
    SDL_FRect rect = { 0, 0, TILE_SIZE, TILE_SIZE };
    struct Player player;
    struct Enemy enemies[QUANTITY_ENEMIES];
    char map[MAP_SIZE][MAP_SIZE + 1];
    unsigned int lastTime = 0, currentTime;
    unsigned int delta;

    initWindow(&window, &renderer);    
    initPlayer(&player);
    initMap(map); 

    while (1) {
        SDL_PollEvent(&event);
        if (event.type == SDL_EVENT_QUIT) {
            break;
        }

        currentTime = SDL_GetTicks();
        delta = currentTime - lastTime;

        readInputs(event, &player); 

        if(delta > 1000/FPS) {
            printf("render!");

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);

            if(player.distanceWalked >= TILE_SIZE) {
                player.isWalking = false;
                player.distanceWalked = 0;
                player.position_x = player.target_position_x;
                player.position_y = player.target_position_y;
                player.diagonalMovement = false;
            }

            if(player.isWalking) {
                if(player.diagonalMovement) {
                    player.distanceWalked += TILE_SIZE / (TILE_SIZE * 120 / player.speed);
                } else {
                    player.distanceWalked += TILE_SIZE / (TILE_SIZE * 50 / player.speed);
                }
                printf("distance walked: %d\n", player.distanceWalked);
            }

            drawMap(renderer, map, &player, rect); 
            drawPlayer(renderer, rect);



            SDL_RenderPresent(renderer);
            lastTime = currentTime;
        }
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
