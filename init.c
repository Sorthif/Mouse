#include "include.h"

mouse initMouse(){
    mouse pMouse;
	pMouse.pos.x = 5;
	pMouse.pos.y = 5;
	pMouse.poops = 0;
    return pMouse;
}

window initWindow(int windowWidth, mouse pMouse){
	window mainWindow;
	mainWindow.x.start = pMouse.pos.x - windowWidth;
	mainWindow.x.end = pMouse.pos.x + windowWidth + 1;
	mainWindow.y.start = pMouse.pos.y - windowWidth;
	mainWindow.y.end = pMouse.pos.y + windowWidth + 1;
    return mainWindow;
}

void allocateMemoryForCats(struct catBox *litterBox, int numberOfCats) {
	litterBox->numberOfCats = numberOfCats;
	litterBox->cats = (struct cat*)calloc(numberOfCats, sizeof(struct cat));
	if (litterBox->cats == NULL) {
		printf("Can't create cats!");
		exit(1);
	}
}

void initCats(char map[][MAPSIZE], struct catBox *litterBox, int amount){
	int k = 0;
	for (int i = 0; i < MAPSIZE; i++) {
		for (int j = 0; j < MAPSIZE; j++) {
			if (map[i][j] == 'C') {
				litterBox->cats[k].lastMoved = 1;
				litterBox->cats[k].x = j;
				litterBox->cats[k].y = i;
				k++;
			}
		}
	}
}

/*================= GENERATE LEVELS ===================
Initiation function for a game. 
difficulty can be changed by the variables in here*/
void generateLevels(int nLevels, game* g)
{
	level* levels = (level*) calloc(nLevels, sizeof(level));
	for(int i = 0; i < nLevels; i++)
	{
		levels[i].nCats = i + 1;
		levels[i].nCheeses = 4 + i * 1;
		levels[i].points = 0;
		levels[i].winpoints = 400 + i * 100;
		levels[i].seed = rand();
		levels[i].size = 100 + i * 20;
	}
	g->currentLevel = 1;
	g->levels = levels;
	g->totalPoints = 0;
	g->nLevels = nLevels;
}