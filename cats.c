#include "include.h"

//allocateMemoryToCats moved to init.c

int moveCats(char map[][MAPSIZE], level *mLevel, struct catBox *litterBox){

	for (int i = 0; i < mLevel->nCats; i++) {
		if(NPCmovement(map, &(litterBox->cats[i]), &mLevel->points) == dead) {
			return dead;
		}
	}
	return alive;
}

static int NPCmovementHelp(char map[][MAPSIZE], struct cat *c, int xValue, int yValue, int xMove, int yMove, int lastM){
	//Helpfunction to NPCmovement.
	if (map[c->y + yValue][c->x + xValue] == '#') {
		return blocked;
	}
	if (map[c->y + yValue][c->x + xValue] == 'o') {
		return blocked;
	}
	map[c->y][c->x] = ' '; //Clears previous location

	//Moves the cat according to switch in NPCmovement
	c->x += xMove;
	c->y += yMove;
	if (map[c->y][c->x] == 'M') {
		return dead; //GAME LOST
	}
	map[c->y][c->x] = 'C';
	c->lastMoved = lastM;
	return walked;
}

int NPCmovement(char map[][MAPSIZE], struct cat *c, int *points) {
	int moveStatus = blocked;
	while (moveStatus == blocked) {
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
	}
	if (moveStatus == dead){
		return dead;
	}
	return walked;
}