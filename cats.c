#include "include.h"

void allocateMemoryForCats(struct catBox *litterBox, int numberOfCats) {
	litterBox->numberOfCats = numberOfCats;
	litterBox->cats = (struct cat*)calloc(numberOfCats, sizeof(struct cat));
	if (litterBox->cats == NULL) {
		printf("Can't create cats!");
		exit(1);
	}
}

static int movementHelp(char map[][MAPSIZE], struct cat *c, int xValue, int yValue, int xMove, int yMove, int lastM){
	if (map[c->y + yValue][c->x + xValue] == '#') {
		return 0;
	}
	if (map[c->y + yValue][c->x + xValue] == 'o') {
		return 0;
	}
	map[c->y][c->x] = ' ';
	// (c->x)--;
	c->x += xMove;
	c->y += yMove;
	if (map[c->y][c->x] == 'M') {
		return 2; //GAME LOST
	}
	map[c->y][c->x] = 'C';
	c->lastMoved = lastM;
	return 1;
}

int NPCmovement(char map[][MAPSIZE], struct cat *c, int *points) {
	_Bool moveSuccessfull = 0, checkLastMoved = 0;
	int moveStatus = 0;
	while (moveStatus == 0) {
		c->lastMoved = weightedDie(c->lastMoved, 70, 10, 10, 10);
		
		switch (c->lastMoved) {
		case 0: // Left
			moveStatus = movementHelp(map, c, -1, 0, -1, 0, 0);
			break;
		case 1: // Down
			moveStatus = movementHelp(map, c, 0, 1, 0, 1, 1);
			break;
		case 2: // Right
			moveStatus = movementHelp(map, c, 1, 0, 1, 0, 3);
			break;
		case 3: // Up
			moveStatus = movementHelp(map, c, 0, -1, 0, -1, 2);
			break;
		}
		if (moveStatus == 2){
			return 0;
		}
	}
	return 1;
}