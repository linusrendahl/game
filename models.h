#include <stdbool.h>

struct Skill {};
struct SkillTree {};
struct UserInput {
};

struct Tile {
	int sprite;
	int speed;
	bool canWalkOver;
};

struct Map {
	char filename[20];
	struct Tile tiles[(25 * 32 * 4) + (17 * 32 * 4)]; // size: 4 screens
};

struct Player {
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
	bool diagonalMovement;
	bool isWalking;
	struct Skill skills[];
};

struct Enemy {
	int xp;
	int hitpoints;
	int speed;
	int attack;
	int position_x;
	int position_y;
	bool isAlive;
	struct Skill skills[];
};
