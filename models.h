#include "SDL3/SDL_render.h"
#include <stdbool.h>
#include <SDL3/SDL.h>
#include "globals.h"

typedef struct GridPosition {
	int x;
	int y;
} GridPosition;

typedef struct Skill {
	SDL_Scancode hotkey; // J:13
	bool active;
	unsigned int activatedTime;
	GridPosition attackingTiles[4];
} Skill;

typedef struct Tile {
	char name;
	SDL_Texture *texture;
	int speed;
	bool tileWalkable;
} Tile;

typedef struct Enemy {
	int xp;
	int maxHitpoints;
	int hitpoints;
	int speed;
	int attack;
	int position_x;
	int position_y;
	SDL_Texture *texture;
	bool isAlive;
} Enemy;

typedef struct Map {
	Tile (*tiles)[MAP_SIZE];
	Enemy *enemies;
} Map;

enum walkingDirection {
	NORTH,
	EAST,
	SOUTH,
	WEST,
	NORTHEAST,
	SOUTHEAST,
	SOUTHWEST,
	NORTHWEST
};

typedef struct Player {
	int xp;
	int hitpoints;
	int mana;
	int speed;
	int attack;
	int magic;
	int distance;	
	int position_x;
	int position_y;
	int target_position_x;
	int target_position_y;
	int distanceWalked;
	Skill skills[4];
	SDL_Texture *texture;
	bool diagonalMovement;
	bool isWalking;
	enum walkingDirection walkingDirection;
	enum walkingDirection facingDirection;
} Player;

typedef struct Game {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    SDL_FRect rect;
    unsigned int lastRenderTime;
    unsigned int currentTime;
    unsigned int timeSinceLastRender;
    Map map;
    Tile tiles[1]; // remove this
    Player player;
} Game;

