#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "../vendored/SDL_image/include/SDL3_image/SDL_image.h"
#include "../models.h"
#include "../globals.h"
#include "player.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "map.h"

#define PLAYER_POS_ROW 20
#define PLAYER_POS_COL 20

void initPlayer(Game *game) {
	char filename[] = "./assets/sprites/character-3.png";
	SDL_Texture *playerTexture;
	playerTexture = IMG_LoadTexture(game->renderer, filename);
	SDL_SetTextureScaleMode(playerTexture, SDL_SCALEMODE_NEAREST);	

	Skill skill;
	skill.hotkey = 13; // J
	skill.active = false;

	game->player.xp = 0;
	game->player.hitpoints = 280;
	game->player.attack = 42;
	game->player.magic = 42;
	game->player.speed = 800;
	game->player.position_x = PLAYER_POS_COL;
	game->player.position_y = PLAYER_POS_ROW;
	game->player.target_position_x = PLAYER_POS_COL;
	game->player.target_position_y = PLAYER_POS_ROW;
	game->player.distanceWalked = 0;
	game->player.diagonalMovement = false;
	game->player.isWalking = false;
	game->player.texture = playerTexture;
	game->player.skills[0] = skill;
}

void playerMove(struct Player *player, char direction[]) {
	if(!player->isWalking) {
		if(strcmp(direction, "west") == 0) {
			player->walkingDirection = WEST;
			player->facingDirection = WEST;
			player->target_position_x = player->position_x - 1;
		} else if (strcmp(direction, "east") == 0) {
			player->walkingDirection = EAST;
			player->facingDirection = EAST;
			player->target_position_x = player->position_x + 1;
		} else if (strcmp(direction, "south") == 0) {
			player->walkingDirection = SOUTH;
			player->facingDirection = SOUTH;
			player->target_position_y = player->position_y + 1;
		} else if (strcmp(direction, "north") == 0) {
			player->walkingDirection = NORTH;
			player->facingDirection = NORTH;
			player->target_position_y = player->position_y - 1;
		}  else if (strcmp(direction, "northwest") == 0) {
			player->walkingDirection = NORTHWEST;
			player->facingDirection = WEST;
			player->diagonalMovement = true;
			player->target_position_y = player->position_y - 1;
			player->target_position_x = player->position_x - 1;
		}  else if (strcmp(direction, "northeast") == 0) {
			player->walkingDirection = NORTHEAST;
			player->facingDirection = EAST;
			player->diagonalMovement = true;
			player->target_position_y = player->position_y - 1;
			player->target_position_x = player->position_x + 1;
		}  else if (strcmp(direction, "southwest") == 0) {
			player->walkingDirection = SOUTHWEST;
			player->facingDirection = WEST;
			player->diagonalMovement = true;
			player->target_position_y = player->position_y + 1;
			player->target_position_x = player->position_x - 1;
		}  else if (strcmp(direction, "southeast") == 0) {
			player->walkingDirection = SOUTHEAST;
			player->facingDirection = EAST;
			player->diagonalMovement = true;
			player->target_position_y = player->position_y + 1;
			player->target_position_x = player->position_x + 1;
		}
		player->isWalking = true;
	}
};

void playerAttack(Game *game, struct Enemy *enemies) {
	int direction = game->player.facingDirection;
	game->player.skills[0].activatedTime = game->currentTime;
	game->player.skills[0].active = true;

	int xDirection;
	int yDirection;
	switch (direction) {
		case 0: //north
			xDirection = 0;
			yDirection = -1;
		break;

		case 1: //east
			xDirection = 1;
			yDirection = 0;
		break;

		case 2: //south
			xDirection = 0;
			yDirection = 1;
		break;

		case 3: //west
			xDirection = -1;
			yDirection = 0;
		break;
	}

	for(int i=1; i <= 6; i++) {
		int targetX = game->player.position_x + (xDirection * i);
		int targetY = game->player.position_y + (yDirection * i);
		game->player.skills[0].attackingTiles[i].x = targetX;
		game->player.skills[0].attackingTiles[i].y = targetY;

		for(int j=0; j < QUANTITY_ENEMIES; j++) {
			if(enemies[j].position_x == targetX && enemies[j].position_y == targetY && enemies[j].isAlive) {
				enemies[j].hitpoints -= (rand() % 100) + game->player.magic;
				if(enemies[j].hitpoints <= 0) {
					enemies[j].isAlive = false;
					game->map.tiles[targetY][targetX].tileWalkable = true;
					enemies[j].hitpoints = 0;
					game->player.xp += 60;
				}
			}
		}
	}
	
}

void drawPlayer(
	Game *game,
	SDL_Renderer *renderer,
	SDL_FRect rect,
	Player *player
	) {
	bool tileWalkable = game->map.tiles[player->target_position_y][player->target_position_x].tileWalkable;
	//printf("player target x: %i, y: %i, with tile: %c\n", player->target_position_x, player->target_position_y, game->map[player->target_position_y][player->target_position_x]);

	// this logic should be in the playerMove() func
	// add logic to isOccupied() -> if enemy is already standing there.
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
			player->distanceWalked += TILE_SIZE / (TILE_SIZE * 71 / game->player.speed);
		} else {
			player->distanceWalked += TILE_SIZE / (TILE_SIZE * 50 / game->player.speed);
		}
	}

	// Collision box: only used for debugging.
	// Create a debugging=true ENV variable in main.c
	//SDL_SetRenderDrawColor(renderer, COLOR_PLAYER);
	//rect.x = 12 * TILE_SIZE;
	//rect.y = 8 * TILE_SIZE;
	//SDL_RenderFillRect(renderer, &rect);
	
	int displaySizeCharacter = 32;
	SDL_FRect dst;
	dst.x = (TILE_SIZE * 12.0f) - 4;
	dst.y = (TILE_SIZE * 8.0f) - 4;
	dst.w = displaySizeCharacter;
	dst.h = displaySizeCharacter;

	SDL_FRect sprite_frame = {0, 0, 16, 16};
	switch (player->walkingDirection) {
		case NORTH:
			sprite_frame.x = 0;
			sprite_frame.y = 0;
		break;	
			case EAST:
			sprite_frame.x = 32;
			sprite_frame.y = 0;
		break;	
		case SOUTH:
			sprite_frame.x = 16;
			sprite_frame.y = 0;
		break;	
		case WEST:
			sprite_frame.x = 48;
			sprite_frame.y = 0;
		break;	
		case NORTHEAST:
			sprite_frame.x = 32;
			sprite_frame.y = 0;
		break;	
		case SOUTHEAST:
			sprite_frame.x = 32;
			sprite_frame.y = 0;
		break;	
		case SOUTHWEST:
			sprite_frame.x = 48;
			sprite_frame.y = 0;
		break;	
		case NORTHWEST:
			sprite_frame.x = 48;
			sprite_frame.y = 0;
		break;

	}

	SDL_RenderTexture(renderer, player->texture, &sprite_frame, &dst);

	SDL_SetRenderDrawColor(renderer, COLOR_HP);
	rect.x = 0;
	rect.y = 0;
	rect.w = GAME_WINDOW_WIDTH;
	rect.h = TILE_SIZE / 2.0f;
	SDL_RenderFillRect(renderer, &rect);

	SDL_SetRenderDrawColor(renderer, COLOR_MANA);
	rect.x = 0;
	rect.y = TILE_SIZE / 2.0f;
	rect.w = GAME_WINDOW_WIDTH;
	rect.h = TILE_SIZE / 2.0f;
	SDL_RenderFillRect(renderer, &rect);

	// draw skills/attack (here for now)
	//printf("attacking tile at x: %i, y: %i\n", game->player.skills[0].attackingTiles[0].x, game->player.skills[0].attackingTiles[0].y);
	SDL_SetRenderDrawColor(renderer, COLOR_HP);
	rect.w = TILE_SIZE;
	rect.h = TILE_SIZE;

			
	if(game->currentTime < game->player.skills[0].activatedTime + 1000 && game->player.skills[0].active) {
		for(int i=0; i < 20; i++) {
			rect.x = (game->player.skills[0].attackingTiles[i].x * TILE_SIZE) - (player->position_x * TILE_SIZE) + (12 * TILE_SIZE) + (player->distanceWalked * (player->position_x - player->target_position_x));
			rect.y = (game->player.skills[0].attackingTiles[i].y * TILE_SIZE) - (player->position_y * TILE_SIZE) + (8 * TILE_SIZE) + (player->distanceWalked * (player->position_y - player->target_position_y));
			SDL_RenderFillRect(renderer, &rect);
		}
	} else {
		game->player.skills[0].active = false;
	}
		
}
