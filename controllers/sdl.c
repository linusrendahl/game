#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "../globals.h"
#include "../models.h"
#include "player.h"

int initWindow(SDL_Window **window, SDL_Renderer **renderer) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return 3;
    }
    if(!SDL_CreateWindowAndRenderer("Game", GAME_WINDOW_WIDTH, GAME_WINDOWS_HEIGHT, SDL_WINDOW_RESIZABLE, window, renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
        return 3;
    }
    return 0;
}

void readInputs(SDL_Event event, struct Player *player) {
        //if(player->target_position_x == player->position_x && player->target_position_y == player->position_y) {
	//	player->isWalking = false;
	//}

        if(event.type == SDL_EVENT_KEY_DOWN) {
            if(event.key.scancode == SDL_SCANCODE_S) {
                playerMove(player, "south");
            }
            if(event.key.scancode == SDL_SCANCODE_W) {
                playerMove(player, "north");
            }
            if(event.key.scancode == SDL_SCANCODE_A) {
                playerMove(player, "west");
            }
            if(event.key.scancode == SDL_SCANCODE_D) {
                playerMove(player, "east");
            }
            if(event.key.scancode == SDL_SCANCODE_Q) {
                playerMove(player, "northwest");
            }
            if(event.key.scancode == SDL_SCANCODE_E) {
                playerMove(player, "northeast");
            }
            if(event.key.scancode == SDL_SCANCODE_C) {
                playerMove(player, "southeast");
            }
            if(event.key.scancode == SDL_SCANCODE_Z) {
                playerMove(player, "southwest");
            }
        }
}
