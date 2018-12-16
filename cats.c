#include "include.h"

//allocateMemoryToCats moved to init.c

int moveCats(char map[][MAPSIZE], level *mLevel, struct catBox *litterBox){

	for (int i = 0; i < mLevel->nCats; i++) {
		if(!NPCmovement(map, &(litterBox->cats[i]), &mLevel->points)) {
			return dead;
		}
	}
	return alive;
}

static int NPCmovementHelp(char map[][MAPSIZE], struct cat *c, int xValue, int yValue, int xMove, int yMove, int lastM){
	//Helpfunction to NPCmovement.
	if (map[c->y + yValue][c->x + xValue] == '#') {
		return 0;
	}
	if (map[c->y + yValue][c->x + xValue] == 'o') {
		return 0;
	}
	map[c->y][c->x] = ' '; //Clears previous location

	//Moves the cat according to switch in NPCmovement
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
		
		switch (c->lastMoved) {//				  cords	 move  
		case 0: // Left							  x  y   x  y  lastMoved
			moveStatus = NPCmovementHelp(map, c, -1, 0, -1, 0, 0);
			break;
		case 1: // Down
			moveStatus = NPCmovementHelp(map, c, 0, 1, 0, 1, 1);
			break;
		case 2: // Right
			moveStatus = NPCmovementHelp(map, c, 1, 0, 1, 0, 3);
			break;
		case 3: // Up
			moveStatus = NPCmovementHelp(map, c, 0, -1, 0, -1, 2);
			break;
		}
		if (moveStatus == 2){
			return 0;
		}
	}
	return 1;
}