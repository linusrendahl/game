#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdlib.h>

#include "../models.h"
#include "../globals.h"

void initEnemies(struct Enemy *enemies) {
	for (int i=0; i < QUANTITY_ENEMIES; i++) {
		enemies[i].hitpoints = 100;
		enemies[i].maxHitpoints = 100;
		enemies[i].position_x = rand() % 40; // move data to a enemies.txt file that complements a map.txt
		enemies[i].position_y = rand() % 40; // move data to a enemies.txt file that complements a map.txt
	}
}

void drawEnemies(SDL_Renderer *renderer, SDL_FRect rect, struct Enemy *enemies, struct Player *player) {
	for (size_t i=0; i < QUANTITY_ENEMIES; i++) {
		SDL_SetRenderDrawColor(renderer, COLOR_ENEMIES);
		rect.x = (enemies[i].position_x * TILE_SIZE) - (player->position_x * TILE_SIZE) + (12 * TILE_SIZE) + (player->distanceWalked * (player->position_x - player->target_position_x));
		rect.y = (enemies[i].position_y * TILE_SIZE) - (player->position_y * TILE_SIZE) + (8 * TILE_SIZE) + (player->distanceWalked * (player->position_y - player->target_position_y));
		rect.h = TILE_SIZE;
		rect.w = TILE_SIZE;
		SDL_RenderFillRect(renderer, &rect);

		SDL_SetRenderDrawColor(renderer, COLOR_MANA);
		rect.y -= 8;
		rect.h = 4;;
		rect.w = (TILE_SIZE * ((float)enemies[i].hitpoints / (float)enemies[i].maxHitpoints));
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

