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

// Change to SDL_GetKeyboardState instead of events.
// Keep an array with all keystates[] = bool that are currently in active state.
// https://wiki.libsdl.org/SDL3/SDL_GetKeyboardState
void readInputs(Game *game) {
        //if(player->target_position_x == player->position_x && player->target_position_y == player->position_y) {
	//	player->isWalking = false;
	//}

        if(game->event.type == SDL_EVENT_KEY_DOWN) {
            if(game->event.key.scancode == SDL_SCANCODE_J) {
                playerAttack(game);
            }
            if(game->event.key.scancode == SDL_SCANCODE_S) {
                playerMove(&game->player, "south");
            }
            if(game->event.key.scancode == SDL_SCANCODE_W) {
                playerMove(&game->player, "north");
            }
            if(game->event.key.scancode == SDL_SCANCODE_A) {
                playerMove(&game->player, "west");
            }
            if(game->event.key.scancode == SDL_SCANCODE_D) {
                playerMove(&game->player, "east");
            }
            if(game->event.key.scancode == SDL_SCANCODE_Q) {
                playerMove(&game->player, "northwest");
            }
            if(game->event.key.scancode == SDL_SCANCODE_E) {
                playerMove(&game->player, "northeast");
            }
            if(game->event.key.scancode == SDL_SCANCODE_C) {
                playerMove(&game->player, "southeast");
            }
            if(game->event.key.scancode == SDL_SCANCODE_Z) {
                playerMove(&game->player, "southwest");
            }
        }
}
