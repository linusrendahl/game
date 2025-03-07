#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <string.h>

#include "../globals.h"
#include "../models.h"

void initMap(char map[40][41]) {
    FILE *fp;
    fp = fopen("assets/maps/map.txt", "r");
    char line[41];
    int i = 0;
    while(fgets(line, 41, fp)) {
       if(!strcmp(line, "\n")) {
            continue;
       }
       memcpy(map[i], line, sizeof(line));
       i++;
    } 
    fclose(fp);
}

void drawMap(SDL_Renderer *renderer, char map[40][41], struct Player *player, SDL_FRect rect) {
    for (size_t i = 0; i < 40; i++) {
            for (size_t j = 0; j < strlen(map[i]); j++) {

                rect.x = (j * TILE_SIZE) + (player->position_x * TILE_SIZE) - (12 * TILE_SIZE);
                rect.y = (i * TILE_SIZE) + (player->position_y * TILE_SIZE) - (8 * TILE_SIZE);

                switch (map[i][j]) {
                case 'A':
                    SDL_SetRenderDrawColor(renderer, 100, 50, 20, 255);
                    break;
                
                case 'B':
                    SDL_SetRenderDrawColor(renderer, 37, 36, 39, 255);
                    break;
                
                default:
                    break;
                }
                SDL_RenderFillRect(renderer, &rect);
            }
    }
}