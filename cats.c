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
void NPCtracking(char map[][MAPSIZE], struct cat *c, int xValue, int yValue, int xMove, int yMove, int lastM) {
	if (map[c->y + yValue][c->x + xValue] == '0')
		c->lastMoved = 0;
	else if (map[c->y + yValue][c->x + xValue] == '1')
		c->lastMoved = 1;
	else if (map[c->y + yValue][c->x + xValue] == '2')
		c->lastMoved = 2;
	else
		c->lastMoved = 3;
}

static int NPCmovementHelp(char map[][MAPSIZE], struct cat *c, int xValue, int yValue, int xMove, int yMove, int lastM){
	//Helpfunction to NPCmovement.
	char *poop = "4567";
	if (strchr(poop, map[c->y + yValue][c->x + xValue])) {
		c->foundPoop = 10;
		map[c->y][c->x] = ' ';
		c->x += xMove;
		c->y += yMove;
		map[c->y][c->x] = 'C';
		return walked;
	}
	if (c->foundPoop > 0) {
		c->foundPoop--;
		if (map[c->y + yValue][c->x + xValue] == '#' || map[c->y + yValue][c->x + xValue] == 'o') {
			return;
		}
		map[c->y][c->x] = ' ';
		c->x += xMove;
		c->y += yMove;
		map[c->y][c->x] = 'C';
		return walked;
	}
	//map[c->y + yValue][c->x + xValue] == '0' || map[c->y + yValue][c->x + xValue] == '1' || map[c->y + yValue][c->x + xValue] == '2' || map[c->y + yValue][c->x + xValue] == '3'
	char *scent = "0123";
	if (strchr(scent, map[c->y + yValue][c->x + xValue])) {
		NPCtracking(map, c, xValue, yValue, xMove, yMove, lastM);
		map[c->y][c->x] = ' ';
		c->x += xMove;
		c->y += yMove;
		if (map[c->y][c->x] == 'M') {
			map[c->y][c->x] = 'C';
			return dead; //GAME LOST
		}
		map[c->y][c->x] = 'C';
		return walked;
	}
	if (map[c->y + yValue][c->x + xValue] == '#' || map[c->y + yValue][c->x + xValue] == 'o') {
		return blocked;
	}
	else {
		map[c->y][c->x] = ' '; //Clears previous location

		//Moves the cat according to switch in NPCmovement
		c->x += xMove;
		c->y += yMove;
		if (map[c->y][c->x] == 'M') {
			map[c->y][c->x] = 'C';
			return dead; //GAME LOST
		}
		map[c->y][c->x] = 'C';
		c->lastMoved = lastM;
		return walked;
	}
}

int NPCmovement(char map[][MAPSIZE], struct cat *c, int *points) {
	int moveStatus = blocked;
	while (moveStatus == blocked) {
		switch (c->lastMoved) {//				  cords	 move  
		case 0: // Left							  x  y   x  y  lastMoved
			moveStatus = NPCmovementHelp(map, c, -1, 0, -1, 0, 0);
			break;
		case 1: // Down
			moveStatus = NPCmovementHelp(map, c, 0, 1, 0, 1, 1);
			break;
		case 2: // Right
			moveStatus = NPCmovementHelp(map, c, 1, 0, 1, 0, 2);
			break;
		case 3: // Up
			moveStatus = NPCmovementHelp(map, c, 0, -1, 0, -1, 3);
			break;
		}
		if (moveStatus == blocked)
			c->lastMoved = weightedDie(c->lastMoved, 95, 2, 2, 1);
	}
	if (moveStatus == dead){
		return dead;
	}
	return walked;
}