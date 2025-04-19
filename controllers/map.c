#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <string.h>
#include "../vendored/SDL_image/include/SDL3_image/SDL_image.h"

#include "../globals.h"
#include "../models.h"
#include "SDL3/SDL_rect.h"

void initMap(Game *game) {
    FILE *fp;
    fp = fopen("assets/maps/map.txt", "r");
    char line[MAP_SIZE + 1];
    int i = 0;
    while(fgets(line, MAP_SIZE + 1, fp)) {
       if(!strcmp(line, "\n")) {
            continue;
       }
        memcpy(game->map[i], line, sizeof(line));
        //memcpy(map[i], line, sizeof(line));
       i++;
    } 
    fclose(fp);
    //game->map = map;
}

void drawMap(Game *game) {
    for (size_t i = 0; i < MAP_SIZE; i++) {
            for (size_t j = 0; j < MAP_SIZE; j++) {
                game->rect.x = (j * TILE_SIZE)
                - (game->player.position_x * TILE_SIZE) + (12 * TILE_SIZE) + (game->player.distanceWalked * (game->player.position_x - game->player.target_position_x));
                game->rect.y = (i * TILE_SIZE) - (game->player.position_y * TILE_SIZE) + (8 * TILE_SIZE) + (game->player.distanceWalked * (game->player.position_y - game->player.target_position_y));

                SDL_FRect dst;

                switch (game->map[i][j]) {
                case 'A':
                    SDL_SetRenderDrawColor(game->renderer, COLOR_A);
                    SDL_RenderFillRect(game->renderer, &game->rect);
                    break;
                
                case 'B':
                    dst.x = game->rect.x;
                    dst.y = game->rect.y;
                    dst.h = 32;
                    dst.w = 32;
                    const SDL_FRect sprite_frame = {0, 0, 16, 16};
                    SDL_RenderTexture(game->renderer, game->tiles[0].texture, &sprite_frame, &dst);
                    break;
                
                default:
                    break;
                }
            }
    }
}
