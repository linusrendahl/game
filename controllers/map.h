#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

void initMap(char map[40][41]);
void drawMap(SDL_Renderer *renderer, char map[40][41], struct Player *player, struct SDL_FRect rect);
