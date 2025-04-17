#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_iostream.h>
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include <SDL3/SDL_gpu.h>
#include "vendored/SDL_image/include/SDL3_image/SDL_image.h"
//#include <SDL3_image/SDL_image.h>
#include <stdio.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_iostream.h>
#include <stdlib.h>
#include "models.h"
#include "globals.h"
#include "controllers/sdl.h"
#include "controllers/player.h"
#include "controllers/enemy.h"
#include "controllers/map.h"

//#define SDL_SOFTWARE_RENDERER   "software"

/** 
 * TODO:
 * - Note: Make it a game asap, dont focus on details.
 *      - Step 1: Refactor code!
 *      - 
 *      - Basic melee attack character.
 *          - Target enemy: 
 *                  - Spacebar > Set player->target = enemy.id
 *                  - which enemies are currently on screen?
 *                  - which enemy is the closest? / order of enemies per distance asc
 *                  - should the game even have auto-attacks at all?
 *                  - First skill: [j] - Great energy beam / wave
 *          - Draw square around enemy.
 *          - Every x.f seconds, player->attackTarget(skill);
 *          - Calculate damage (randomized within an interval, depending on attack power).
 *          - Enemy.hitpoints -= damage
 *          - Enemy.hitpoints <= 0 = dead
 *          - Remove enemy from array of drawn enemies.
 *          - Set a respawn timer, respawn after x seconds
 *          - persist data in sqlite
 *      - Respawn enemies after x seconds.
 *      - Gain experience for killing mobs.
 *      - Enemies blockable.
 *      - Enemies move towards player.
 *      - Enemies melee basic attacks.
 *      - Deal damage to player > dead state.
 *      - Healing: spells/potions/auto/leech/etc.
 *
 *
 *
 * - Main game:
 *      - Grind mobs for resources/experience
 *      - Grind bosses for items/fragments/map unlocks.
 * - Define minimal game-loop.
 * - Create a hub with portals to maps.
 *
 * SKILLS:
 * Collision on enemies.
 * Gain experience / levels / stats.
 * Enemy attacks.
 * Draw sprites.
 * Time to clean up all code / organize / rewrite.
 *
 * Gameplay:
 * - ability to destroy terrain.
 * - procedurally generated maps.
 * - map levels/stairs, portals to other maps.
 * - loot & crafting.
 * - infinite scaling.
 * - coop 5 player teams / matchmaking.
 * - boss fights (telegraphed attacks).
 * - single class, infinite builds (skill tree)
 * - theme of game?
 *   Items with random affixes (POE/D2)
 * 
 * - write tutorial as we go along
 *
 *   Make it a hackable game:
 *   - All game configs/database/textures/maps/etc,
 *   are easily editable. moddable.
 *   - community driven: create sprites, maps, enemies, etc.
 * **/
int main(int argc, char *argv[]) {
    SDL_Window *window; 
    SDL_Renderer *renderer;
    //SDL_Surface *surface;
    //SDL_LoadBMP(const char *file)
    //static SDL_Texture *texture = NULL;
    SDL_Event event;
    SDL_FRect rect = { 0, 0, TILE_SIZE, TILE_SIZE };
    struct Player player;
    struct Enemy enemies[QUANTITY_ENEMIES];
    char map[MAP_SIZE][MAP_SIZE + 1];
    unsigned int lastTime = 0, currentTime;
    unsigned int delta;

    initWindow(&window, &renderer);
    initPlayer(&player);
    initEnemies(enemies);
    initMap(map); 

    //SDL_GPUDevice *device;
    //const SDL_GPUShaderCreateInfo *createinfo;
    //struct SDL_GPUShader *shader = SDL_CreateGPUShader(device, createinfo);

    char filename[] = "./assets/sprites/character-3.png";
    char floorfile[] = "./assets/sprites/floor.png";
    SDL_Texture *playerTexture;
    SDL_Texture *floorTexture;
    playerTexture = IMG_LoadTexture(renderer, filename);
    floorTexture = IMG_LoadTexture(renderer, floorfile);
    //SDL_SetDefaultTextureScaleMode(renderer, SDL_SCALEMODE_NEAREST);
    SDL_SetTextureScaleMode(playerTexture, SDL_SCALEMODE_NEAREST);
    SDL_SetTextureScaleMode(floorTexture, SDL_SCALEMODE_NEAREST);
    SDL_SetRenderScale(renderer, RENDER_SCALE, RENDER_SCALE);
    //SDL_SetRenderColorScale(renderer, 1.2f);
    //SDL_SetTextureColorModFloat(playerTexture, 1.5f, 1.5f, 1.5f);

    while (1) {
        SDL_PollEvent(&event);
        if (event.type == SDL_EVENT_QUIT) {
            break;
        }

        currentTime = SDL_GetTicks();
        delta = currentTime - lastTime;
        
        readInputs(event, &player); 

        if(delta > 1000/FPS) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);

            drawMap(renderer, map, &player, rect, floorTexture); 
            drawPlayer(renderer, rect, &player, map, playerTexture);
            drawEnemies(renderer, rect, enemies, &player);

            SDL_RenderPresent(renderer);
            lastTime = currentTime;
        }
    }

    SDL_DestroyTexture(playerTexture);
    //SDL_DestroySurface(playerSurface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
