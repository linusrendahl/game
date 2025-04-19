#include "SDL3/SDL_render.h"
#include <stdbool.h>
#include <SDL3/SDL.h>
#include "globals.h"

struct Skill {
	char hotkey;
};


struct SkillTree {
	// graph / matrix
};

struct UserInput {
	// current_input
	// next_input (queue)
};

typedef struct Tile {
	char name;
	SDL_Texture *texture;
	int speed;
	bool tileWalkable;
} Tile;

typedef struct Map {
	char (*map)[40];
	Tile floor;
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
	SDL_Texture *texture;
	bool diagonalMovement;
	bool isWalking;
	enum walkingDirection walkingDirection;
	struct Skill skills[];
} Player;

struct Enemy {
	int xp;
	int maxHitpoints;
	int hitpoints;
	int speed;
	int attack;
	int position_x;
	int position_y;
	bool isAlive;
	struct Skill skills[];
};

typedef struct Game {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    SDL_FRect rect;
    unsigned int lastRenderTime;
    unsigned int currentTime;
    unsigned int timeSinceLastRender;
    char (*map)[MAP_SIZE];
    Tile tiles[1];
    Player player;
} Game;

