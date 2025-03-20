#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "../models.h"
#include "../globals.h"
#include "player.h"
#include "map.h"

#define PLAYER_POS_ROW 20
#define PLAYER_POS_COL 20

void initPlayer(struct Player *player) {
	player->xp = 200;
	player->attack = 42;
	player->speed = 400;
	player->position_x = PLAYER_POS_COL;
	player->position_y = PLAYER_POS_ROW;
	player->target_position_x = PLAYER_POS_COL;
	player->target_position_y = PLAYER_POS_ROW;
	player->distanceWalked = 0;
	player->diagonalMovement = false;
	player->isWalking = false;
}

void playerMove(struct Player *player, char direction[]) {
	if(!player->isWalking) {
		if(strcmp(direction, "west") == 0) {
			player->target_position_x = player->position_x - 1;
		} else if (strcmp(direction, "east") == 0) {
			player->target_position_x = player->position_x + 1;
		} else if (strcmp(direction, "south") == 0) {
			player->target_position_y = player->position_y + 1;
		} else if (strcmp(direction, "north") == 0) {
			player->target_position_y = player->position_y - 1;
		}  else if (strcmp(direction, "northwest") == 0) {
			player->diagonalMovement = true;
			player->target_position_y = player->position_y - 1;
			player->target_position_x = player->position_x - 1;
		}  else if (strcmp(direction, "northeast") == 0) {
			player->diagonalMovement = true;
			player->target_position_y = player->position_y - 1;
			player->target_position_x = player->position_x + 1;
		}  else if (strcmp(direction, "southwest") == 0) {
			player->diagonalMovement = true;
			player->target_position_y = player->position_y + 1;
			player->target_position_x = player->position_x - 1;
		}  else if (strcmp(direction, "southeast") == 0) {
			player->diagonalMovement = true;
			player->target_position_y = player->position_y + 1;
			player->target_position_x = player->position_x + 1;
		}
		player->isWalking = true;
	}

	printf("Player target is %s [x: %d, y: %d]. Position is [x: %d, y: %d]\n", direction, player->target_position_x, player->target_position_y, player->position_x, player->position_y);

};

void playerAttack(struct Player *player, struct Enemy *enemy) {
	float random = (rand() % 100) / 100.0; 
	int damage = round(player->attack * random);
	enemy->hitpoints -= damage;
	printf("Enemy attacked and loses %d \n", damage);
}

void drawPlayer(SDL_Renderer *renderer, SDL_FRect rect, struct Player *player, char map[MAP_SIZE][MAP_SIZE + 1]) {
	bool tileWalkable = map[player->target_position_y][player->target_position_x] != 'A';
	if(player->distanceWalked >= TILE_SIZE || !tileWalkable) {
		player->isWalking = false;
		player->distanceWalked = 0;
		if(!tileWalkable) {
			player->target_position_x = player->position_x;
			player->target_position_y = player->position_y;
		} else {
			player->position_x = player->target_position_x;
			player->position_y = player->target_position_y;
		}
		player->diagonalMovement = false;
	}

	if(player->isWalking) {
		if(player->diagonalMovement) {
			player->distanceWalked += TILE_SIZE / (TILE_SIZE * 100 / player->speed);
		} else {
			player->distanceWalked += TILE_SIZE / (TILE_SIZE * 50 / player->speed);
		}
	}

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
