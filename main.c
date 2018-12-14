#include "include.h"

int main(void) {
	
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

	//Deklarera
	int x = spawnLocations[0], y = spawnLocations[1], points = 0;
	int windowWidth = WINDOW;
	window mainWindow;
	mainWindow.x.start = x - windowWidth;
	mainWindow.x.end = x + windowWidth + 1;
	mainWindow.y.start = y - windowWidth;
	mainWindow.y.end = y + windowWidth + 1;

	while (1) {
		if (points == 1200) {
			printf("Congratulations! You won!\nPoints earned: %d", points);
			getchar();
			break;
		}
		CLEAR;
		if(!moveMouse(map, &x, &y, &mainWindow, &points))
		{
			break;
		}
		for (int i = 0; i < AMOUNTOFCATS; i++) {
			if(!NPCmovement(map, &litterBox.cats[i], &points))
			{
				break;
			}
		}
	}
	gameLost(map, points);
}