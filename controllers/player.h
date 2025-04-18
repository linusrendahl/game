#include <stdbool.h>
#include <SDL3/SDL.h>
#include "../globals.h"

void initPlayer(Game *game);
void playerMove(Player *player, char direction[]);
void playerAttack(Player *player, struct Enemy *enemy);
void attacked(void);
bool isAlive(void);
void drawPlayer(Game *game, SDL_Renderer *renderer, SDL_FRect rect, Player *player, char map[MAP_SIZE][MAP_SIZE]);

