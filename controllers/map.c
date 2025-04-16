#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <string.h>

#include "../globals.h"
#include "../models.h"
#include "SDL3/SDL_rect.h"

void initMap(char map[MAP_SIZE][MAP_SIZE + 1]) {
    FILE *fp;
    fp = fopen("assets/maps/map.txt", "r");
    char line[MAP_SIZE + 1];
    int i = 0;
    while(fgets(line, MAP_SIZE + 1, fp)) {
       if(!strcmp(line, "\n")) {
            continue;
       }
       memcpy(map[i], line, sizeof(line));
       i++;
    } 
    fclose(fp);
}

void drawMap(SDL_Renderer *renderer, char map[MAP_SIZE][MAP_SIZE + 1], struct Player *player, SDL_FRect rect, SDL_Texture *floorTexture) {
    for (size_t i = 0; i < MAP_SIZE; i++) {
            for (size_t j = 0; j < strlen(map[i]); j++) {
                rect.x = (j * TILE_SIZE) - (player->position_x * TILE_SIZE) + (12 * TILE_SIZE) + (player->distanceWalked * (player->position_x - player->target_position_x));
                rect.y = (i * TILE_SIZE) - (player->position_y * TILE_SIZE) + (8 * TILE_SIZE) + (player->distanceWalked * (player->position_y - player->target_position_y));

                SDL_FRect dst;

                switch (map[i][j]) {
                case 'A':
                    SDL_SetRenderDrawColor(renderer, COLOR_A);
                    SDL_RenderFillRect(renderer, &rect);
                    break;
                
                case 'B':
                    dst.x = rect.x;
                    dst.y = rect.y;
                    dst.h = 32;
                    dst.w = 32;
                    const SDL_FRect sprite_frame = {0, 0, 16, 16};
                    SDL_RenderTexture(renderer, floorTexture, &sprite_frame, &dst);
                    break;
                
                default:
                    break;
                }
            }
    }
}
