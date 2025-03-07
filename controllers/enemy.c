#include <stdio.h>
#include <stdlib.h>

#include "../models.h"

void enemiesSpawn(struct Enemy enemies[], size_t quantityEnemies) {
	for (int i=0; i < quantityEnemies; i++) {
		enemies[i].hitpoints = 100;
		enemies[i].position_x = rand() % 100;
		enemies[i].position_y = rand() % 100;
	}
}

