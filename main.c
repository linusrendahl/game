// SDL3 install https://www.youtube.com/watch?v=Wuj7JJ7QcHk
// makefile: clang main.c -o main `pkg-config --libs --cflags sdl2
// https://wiki.libsdl.org/SDL3/README/cmake
// cmake -S . -B build -DSDL_FRAMEWORK=ON -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64"
// cmake --build build
// cmake --install build --prefix ~/SDL
// Move sdl3.framework to ~/Library/Frameworks/
// create maps in ascii files (easier to edit). load ascii to array > render for each character to tile.
// tiling POE: https://www.pathofexile.com/forum/view-thread/55091
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>

#include "models.h"
#include "globals.h"
#include "controllers/sdl.h"
#include "controllers/player.h"
#include "controllers/enemy.h"
#include "controllers/map.h"

int main(int argc, char *argv[]) {
    SDL_Window *window; 
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Event event;
    SDL_FRect rect = { 0, 0, TILE_SIZE, TILE_SIZE };
    struct Player player;
	struct Enemy enemies[QUANTITY_ENEMIES];
    char map[40][41];

    initWindow(&window, &renderer);    
	initPlayer(&player);
    initMap(map); 
   
    while (1) {
        SDL_PollEvent(&event);
        if (event.type == SDL_EVENT_QUIT) {
            break;
        }

        readInputs(event, &player); 

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        
        drawMap(renderer, map, &player, rect); 
        drawPlayer(renderer, rect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
