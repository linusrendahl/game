#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "../globals.h"

void initEnemies(struct Enemy enemies[QUANTITY_ENEMIES]);
void drawEnemies(SDL_Renderer *renderer, SDL_FRect rect, struct Enemy *enemies, struct Player *player);
void enemiesSpawn(struct Enemy enemies[], int);
