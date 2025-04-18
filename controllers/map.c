#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <string.h>
#include "../vendored/SDL_image/include/SDL3_image/SDL_image.h"

#include "../globals.h"
#include "../models.h"
#include "SDL3/SDL_rect.h"

void initMap(Game *game, Map *theMap, char map[MAP_SIZE][MAP_SIZE]) {
    //deprecate this
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

    // load into game object
    FILE *fptwo;
    fptwo = fopen("assets/maps/map.txt", "r");
    char linetwo[MAP_SIZE + 1];
    int itwo = 0;
    while(fgets(linetwo, sizeof(linetwo), fptwo)) {
       if(!strcmp(linetwo, "\n")) {
            continue;
       }
        
        printf("line: %s\n", linetwo);
        //memcpy(game->map[itwo], linetwo, sizeof(linetwo));
       itwo++;
    } 
    fclose(fp);

    //test
    //for(itwo = 0; itwo < MAP_SIZE * MAP_SIZE; itwo++) {
    //    printf("%c", game->map[itwo]); 
    //}


    char floorfile[] = "./assets/sprites/floor.png";
    SDL_Texture *floorTexture;
    floorTexture = IMG_LoadTexture(game->renderer, floorfile);
    SDL_SetTextureScaleMode(floorTexture, SDL_SCALEMODE_NEAREST);
    theMap->floor.texture = floorTexture;
}

void drawMap(Game *game, Map *theMap, char map[MAP_SIZE][MAP_SIZE]) {
    for (size_t i = 0; i < MAP_SIZE; i++) {
            for (size_t j = 0; j < MAP_SIZE; j++) {
                game->rect.x = (j * TILE_SIZE)
                - (game->player.position_x * TILE_SIZE) + (12 * TILE_SIZE) + (game->player.distanceWalked * (game->player.position_x - game->player.target_position_x));
                game->rect.y = (i * TILE_SIZE) - (game->player.position_y * TILE_SIZE) + (8 * TILE_SIZE) + (game->player.distanceWalked * (game->player.position_y - game->player.target_position_y));

                SDL_FRect dst;

                //switch (map[i][j]) {
                switch (game->map[(i * MAP_SIZE) + j]) {
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
                    SDL_RenderTexture(game->renderer, theMap->floor.texture, &sprite_frame, &dst);
                    break;
                
                default:
                    break;
                }
            }
    }
}
