#include "include.h"

int NPCmovement(char map[][MAPSIZE], int *x, int *y, int *points, int *lastMoved) {
	_Bool moveSuccessfull = 0, checkLastMoved = 0;
	int movement;
	while (moveSuccessfull == 0) {
		if (checkLastMoved == 0) {
			movement = *lastMoved;
		}
		else
			movement = randomMovementGenerator(1, 4, *lastMoved);
		switch (movement) {
		case 1: // Left
			if (map[*y][*x - 1] == '#') {
				checkLastMoved = 1;
				break;
			}
			if (map[*y][*x - 1] == 'o') {
				checkLastMoved = 1;
				break;
			}
			map[*y][*x] = ' ';
			(*x)--;
			if (map[*y][*x] == 'M') {
				return 0; //GAME LOST
			}
			map[*y][*x] = 'C';
			moveSuccessfull = 1;
			*lastMoved = 1;
			break;
		case 2: // Down
			if (map[*y + 1][*x] == '#') {
				checkLastMoved = 1;
				break;
			}
			if (map[*y + 1][*x] == 'o') {
				checkLastMoved = 1;
				break;
			}
			map[*y][*x] = ' ';
			(*y)++;
			if (map[*y][*x] == 'M') {
				return 0; //GAME LOST
			}
			map[*y][*x] = 'C';
			moveSuccessfull = 1;
			*lastMoved = 2;
			break;
		case 3: // Up
			if (map[*y - 1][*x] == '#') {
				checkLastMoved = 1;
				break;
			}
			if (map[*y - 1][*x] == 'o') {
				checkLastMoved = 1;
				break;
			}
			map[*y][*x] = ' ';
			(*y)--;
			if (map[*y][*x] == 'M') {
				return 0; //GAME LOST
			}
			map[*y][*x] = 'C';
			moveSuccessfull = 1;
			*lastMoved = 3;
			break;
		case 4: // Right
			if (map[*y][*x + 1] == '#') {
				checkLastMoved = 1;
				break;
			}
			if (map[*y][*x + 1] == 'o') {
				checkLastMoved = 1;
				break;
			}
			map[*y][*x] = ' ';
			(*x)++;
			if (map[*y][*x] == 'M') {
				return 0; //GAME LOST
			}
			map[*y][*x] = 'C';
			moveSuccessfull = 1;
			*lastMoved = 4;
			break;
		}
	}
	return 1;
}