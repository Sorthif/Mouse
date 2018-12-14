#include "include.h"

void allocateMemoryForCats(struct catBox *litterBox, int numberOfCats) {
	litterBox->numberOfCats = numberOfCats;
	litterBox->cats = (struct cat*)calloc(numberOfCats, sizeof(struct cat));
	if (litterBox->cats == NULL) {
		printf("Can't create cats!");
		exit(1);
	}
}


int NPCmovement(char map[][MAPSIZE], struct cat *c, int *points) {
	_Bool moveSuccessfull = 0, checkLastMoved = 0;
	while (moveSuccessfull == 0) {
		c->lastMoved = weightedDie(c->lastMoved, 70, 10, 10, 10);
		
		switch (c->lastMoved) {
		case 0: // Left
			if (map[c->y][c->x - 1] == '#') {
				break;
			}
			if (map[c->y][c->x - 1] == 'o') {
				break;
			}
			map[c->y][c->x] = ' ';
			(c->x)--;
			if (map[c->y][c->x] == 'M') {
				return 0; //GAME LOST
			}
			map[c->y][c->x] = 'C';
			moveSuccessfull = 1;
			c->lastMoved = 0;
			break;
		case 1: // Down
			if (map[c->y + 1][c->x] == '#') {
				break;
			}
			if (map[c->y + 1][c->x] == 'o') {
				break;
			}
			map[c->y][c->x] = ' ';
			(c->y)++;
			if (map[c->y][c->x] == 'M') {
				return 0; //GAME LOST
			}
			map[c->y][c->x] = 'C';
			moveSuccessfull = 1;
			c->lastMoved = 1;
			break;
		case 2: // Right
			if (map[c->y][c->x + 1] == '#') {
				break;
			}
			if (map[c->y][c->x + 1] == 'o') {
				break;
			}
			map[c->y][c->x] = ' ';
			(c->x)++;
			if (map[c->y][c->x] == 'M') {
				return 0; //GAME LOST
			}
			map[c->y][c->x] = 'C';
			moveSuccessfull = 1;
			c->lastMoved = 3;
			break;
		case 3: // Up
			if (map[c->y - 1][c->x] == '#') {
				break;
			}
			if (map[c->y - 1][c->x] == 'o') {
				break;
			}
			map[c->y][c->x] = ' ';
			(c->y)--;
			if (map[c->y][c->x] == 'M') {
				return 0; //GAME LOST
			}
			map[c->y][c->x] = 'C';
			moveSuccessfull = 1;
			c->lastMoved = 2;
			break;

		}
	}
	return 1;
}