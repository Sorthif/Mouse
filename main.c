#include "include.h"

int main(void) {
	int lost = 0, turns = 0;

	char map[MAPSIZE][MAPSIZE];
	srand(time(0));

	struct catBox litterBox;

	makeMap(5, 5, 100, AMOUNTOFCATS, 20);
	readMap("RandomMap.mp", map);

	int spawnLocations[100];
	getSpawnLocations(map, spawnLocations);
	allocateMemoryForCats(&litterBox, AMOUNTOFCATS);

	for (int i = 2, j = 3, k = 0; k < AMOUNTOFCATS; i = i + 2, j = j + 2, k++) {
		litterBox.cats[k].lastMoved = 1;
		litterBox.cats[k].x = spawnLocations[i];
		litterBox.cats[k].y = spawnLocations[j];
	}

	//deklarera musen
	mouse pMouse;
	pMouse.points = 0;
	pMouse.pos.x = spawnLocations[0];
	pMouse.pos.y = spawnLocations[1];

	//Deklarera Föstret
	int windowWidth = WINDOW;
	window mainWindow;
	mainWindow.x.start = pMouse.pos.x - windowWidth;
	mainWindow.x.end = pMouse.pos.x + windowWidth + 1;
	mainWindow.y.start = pMouse.pos.y - windowWidth;
	mainWindow.y.end = pMouse.pos.y + windowWidth + 1;

	CLEAR;
	while (!lost) {
		if (pMouse.points == 1200) {
			printf("Congratulations! You won!\nPoints earned: %d", pMouse.points);
			getchar();
			exit(1);
		}
		int walked = 2;
		while(walked == 2)
		{
			printSeeableMap(map, mainWindow.y.start, mainWindow.y.end, mainWindow.x.start, mainWindow.x.end);
			printf("\nturns: %d", turns);
			printUI(pMouse.points);
			pMouse.direction = GETCHARINPUT;
			CLEAR;
			if(pMouse.direction == ' ')
			{
				break;
			}
			walked = moveMouse(map, &pMouse, &mainWindow);
			if(walked == 0)
			{
				lost = 1;
			}
		}

		for (int i = 0; i < AMOUNTOFCATS; i++) {
			if(!NPCmovement(map, &litterBox.cats[i], &pMouse.points))
			{
				lost = 1;
			}
		}
		turns++;
	}
	gameLost(map, pMouse.points);
	exit(1);
}