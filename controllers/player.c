#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "../models.h"
#include "../globals.h"
#include "player.h"

#define moveDistanceStep 1
#define PLAYER_POS_ROW 8
#define PLAYER_POS_COL 12 

void initPlayer(struct Player *player) {
	player->xp = 200;
	player->attack = 42;
	player->position_x = PLAYER_POS_COL;
	player->position_y = PLAYER_POS_ROW;
}

void playerMove(struct Player *player, char direction[]) {
	// check target tile
	// if can walk on tile, walk. else dont.
	if(strcmp(direction, "west") == 0) {
		player->position_x += moveDistanceStep;
	} else if (strcmp(direction, "east") == 0) {
		player->position_x -= moveDistanceStep;
	} else if (strcmp(direction, "south") == 0) {
		player->position_y -= moveDistanceStep;
	} else if (strcmp(direction, "north") == 0) {
		player->position_y += moveDistanceStep;
	}  else if (strcmp(direction, "northwest") == 0) {
		player->position_y += moveDistanceStep;
		player->position_x += moveDistanceStep;
	}  else if (strcmp(direction, "northeast") == 0) {
		player->position_y += moveDistanceStep;
		player->position_x -= moveDistanceStep;
	}  else if (strcmp(direction, "southwest") == 0) {
		player->position_y -= moveDistanceStep;
		player->position_x += moveDistanceStep;
	}  else if (strcmp(direction, "southeast") == 0) {
		player->position_y -= moveDistanceStep;
		player->position_x -= moveDistanceStep;
	}

	printf("Player moved to the %s [x: %d, y: %d]\n", direction, player->position_x, player->position_y);

};

void playerAttack(struct Player *player, struct Enemy *enemy) {
	float random = (rand() % 100) / 100.0; 
	int damage = round(player->attack * random);
	enemy->hitpoints -= damage;
	printf("Enemy attacked and loses %d \n", damage);
}

void drawPlayer(SDL_Renderer *renderer, SDL_FRect rect) {
	SDL_SetRenderDrawColor(renderer, COLOR_PLAYER);
    rect.x = 12 * TILE_SIZE;
    rect.y = 8 * TILE_SIZE;
    SDL_RenderFillRect(renderer, &rect);

	SDL_SetRenderDrawColor(renderer, COLOR_HP);
    rect.x = 0;
    rect.y = 0;
	rect.w = GAME_WINDOW_WIDTH;
	rect.h = TILE_SIZE / 2;
    SDL_RenderFillRect(renderer, &rect);

	SDL_SetRenderDrawColor(renderer, COLOR_MANA);
    rect.x = 0;
    rect.y = TILE_SIZE / 2;
	rect.w = GAME_WINDOW_WIDTH;
	rect.h = TILE_SIZE / 2;
    SDL_RenderFillRect(renderer, &rect);
}