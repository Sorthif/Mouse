#include "include.h"

int main(void) {
	
	char map[MAPSIZE][MAPSIZE], movement = ' ';
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
	// YS = Y start, YE = Y end, XS = X start, XE = X end.
	int x = spawnLocations[0], y = spawnLocations[1], seeableMapYS = y - WINDOW, seeableMapYE = y + WINDOW + 1, seeableMapXS = x - WINDOW, seeableMapXE = x + WINDOW + 1, points = 0;
	//cats[0].x = spawnLocations[2], cats[0].y = spawnLocations[3], cats[1].x = spawnLocations[4], cats[1].y = spawnLocations[5]; // NPC startlocation.

	while (1) {
		if (points == 1200) {
			printf("Congratulations! You won!\nPoints earned: %d", points);
			getchar();
			break;
		}
		CLEAR;
		if(!moveMouse(map, &movement, &x, &y, &seeableMapYS, &seeableMapYE, &seeableMapXS, &seeableMapXE, &points))
		{
			break;
		}
		for (int i = 0; i < AMOUNTOFCATS; i++) {
			if(!NPCmovement(map, &litterBox.cats[i].x, &litterBox.cats[i].y, &points, &litterBox.cats[i].lastMoved))
			{
				break;
			}
		}
	}
	gameLost(map, points);
}