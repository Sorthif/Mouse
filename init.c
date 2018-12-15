#include "include.h"

mouse initMouse(int spawnLocations[]){
    mouse pMouse;
	pMouse.pos.x = spawnLocations[0];
	pMouse.pos.y = spawnLocations[1];
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

void initCats(struct catBox *litterBox, int amount, int spawnLocations[]){
	for (int i = 2, j = 3, k = 0; k < amount; i = i + 2, j = j + 2, k++) {
		litterBox->cats[k].lastMoved = 1;
		litterBox->cats[k].x = spawnLocations[i];
		litterBox->cats[k].y = spawnLocations[j];
	}
}

