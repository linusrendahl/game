#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "models.h"
#include "globals.h"
#include "controllers/sdl.h"
#include "controllers/player.h"
#include "controllers/enemy.h"
#include "controllers/map.h"

/** 
 * Walking
 * 1. Standing still
 * 2. Read input
 * 3. Set destination tile/player position
 * 4. isWalking = true
 * 5. if isWalking, do not change destionation tile / ignore read input (or put in queue).
 * 6. when arrived, isWalking = true. (back to 1 / next in queue).
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

        /** 
         * UserInput struct: set list of keyboard inputs.
         * UserInput is then used by several structs:
         * pass UserInput to userController, read scancode, decide what to do.
         * (why not just pass the SDL_Event instead?)
         * Player:
         * Skills: 
         * Menu:
         * TargetEnemy: 
         * **/ 

        readInputs(event, &player); 

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        
        drawMap(renderer, map, &player, rect); 
        drawPlayer(renderer, rect);

        SDL_RenderPresent(renderer);
        lastTime = currentTime;
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
