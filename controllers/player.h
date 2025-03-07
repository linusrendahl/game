#include <stdbool.h>

void initPlayer(struct Player *player);
void playerMove(struct Player *player, char direction[]);
void playerAttack(struct Player *player, struct Enemy *enemy);
void attacked(void);
bool isAlive(void);
void drawPlayer(SDL_Renderer *renderer, SDL_FRect rect);

