#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../vendored/SDL_image/include/SDL3_image/SDL_image.h"
#include "../models.h"
#include "../globals.h"

// move to globel helper functions
GridPosition getRandomTileWalkable(Game *game) {
	//@todo: dont spawn multiple enemies on the same tile.
	GridPosition pos = {0, 0};
	while(true) {
		pos.x = rand() % 40;
		pos.y = rand() % 40;
		bool tileWalkable = game->map[pos.y][pos.x] != 'A';
		if(tileWalkable) {
			break;
		}
	}
	//printf("enemy at x: %i, y: %i, with tile: %c\n", pos.x, pos.y, game->map[pos.y][pos.x]);
	return pos;
}

void initEnemies(Game *game, struct Enemy *enemies) {
	char filename[] = "./assets/sprites/dummy.png";
	SDL_Texture *dummy;
	dummy = IMG_LoadTexture(game->renderer, filename);
	SDL_SetTextureScaleMode(dummy, SDL_SCALEMODE_NEAREST);	

	for (int i=0; i < QUANTITY_ENEMIES; i++) {
		GridPosition pos = getRandomTileWalkable(game);
		enemies[i].hitpoints = 100;
		enemies[i].maxHitpoints = 100;
		enemies[i].position_x = pos.x;
		enemies[i].position_y = pos.y;
		enemies[i].texture = dummy;
	}
}

void drawEnemies(SDL_Renderer *renderer, SDL_FRect rect, struct Enemy *enemies, struct Player *player) {
	for (size_t i=0; i < QUANTITY_ENEMIES; i++) {
		SDL_SetRenderDrawColor(renderer, COLOR_ENEMIES);
		rect.x = (enemies[i].position_x * TILE_SIZE) - (player->position_x * TILE_SIZE) + (12 * TILE_SIZE) + (player->distanceWalked * (player->position_x - player->target_position_x));
		rect.y = (enemies[i].position_y * TILE_SIZE) - (player->position_y * TILE_SIZE) + (8 * TILE_SIZE) + (player->distanceWalked * (player->position_y - player->target_position_y));
		rect.h = TILE_SIZE;
		rect.w = TILE_SIZE;
		//SDL_RenderFillRect(renderer, &rect);

		int displaySizeCharacter = 32;
		SDL_FRect dst;
		dst.x = rect.x - 8;
		dst.y = rect.y - 8;
		dst.w = displaySizeCharacter;
		dst.h = displaySizeCharacter;
		SDL_FRect sprite_frame = {0, 0, 16, 16};

		SDL_RenderTexture(renderer, enemies[i].texture, &sprite_frame, &dst);


		SDL_SetRenderDrawColor(renderer, 30, 30, 30, 120);
		rect.y -= 16;
		rect.x -= 8;
		rect.h = 6;
		rect.w = (TILE_SIZE + 1);
		SDL_RenderFillRect(renderer, &rect);
	
		SDL_SetRenderDrawColor(renderer, COLOR_HP);
		rect.y += 1;
		rect.x += 1;
		rect.h = 4;
		rect.w = (TILE_SIZE * ((float)enemies[i].hitpoints / (float)enemies[i].maxHitpoints) - 1);
		SDL_RenderFillRect(renderer, &rect);

	}
}

void enemiesSpawn(struct Enemy enemies[], size_t quantityEnemies) {
	for (int i=0; i < quantityEnemies; i++) {
		enemies[i].hitpoints = 100;
		enemies[i].position_x = rand() % 100;
		enemies[i].position_y = rand() % 100;
	}
}

