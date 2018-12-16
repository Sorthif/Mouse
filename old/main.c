#include "include.h"

int main(void) {

	char map[MAPSIZE][MAPSIZE], movement = ' ';
	srand(time(0));
	int cats = 10;
	makeMap(5, 5, 100, cats, 20);
	buildMapLevel1(map);
	int spawnLocations[20]; 
	getSpawnLocations(map, spawnLocations);

	// YS = Y start, YE = Y end, XS = X start, XE = X end.
	int x = spawnLocations[0], y = spawnLocations[1], seeableMapYS = y - WINDOW, seeableMapYE = y + WINDOW + 1, seeableMapXS = x - WINDOW, seeableMapXE = x + WINDOW + 1, points = 0;
	int AI1X = spawnLocations[2], AI1Y = spawnLocations[3], AI2X = spawnLocations[4], AI2Y = spawnLocations[5]; // NPC startlocation.
	int lastMovedAI1 = 1, lastMovedAI2 = 1;
	while (1) {
		if (points == 800) {
			printf("Congratulations! You won!\nPoints earned: %d", points);
			getchar();
			break;
		}
		CLEAR;
		moveMouse(map, &movement, &x, &y, &seeableMapYS, &seeableMapYE, &seeableMapXS, &seeableMapXE, &points);
		NPCmovement(map, &AI1X, &AI1Y, &points, &lastMovedAI1);
		NPCmovement(map, &AI2X, &AI2Y, &points, &lastMovedAI2);

	}

	return 0;
}