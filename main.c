#include "include.h"

int main(void) {

	char map[MAPSIZE][MAPSIZE], movement = ' ';
	srand(time(0));
	int numbOfCats = 2;
	struct cat cats[2];
	makeMap(5, 5, 100, numbOfCats, 20);
	buildMapLevel1(map);
	int spawnLocations[20];
	getSpawnLocations(map, spawnLocations);

	// YS = Y start, YE = Y end, XS = X start, XE = X end.
	int x = spawnLocations[0], y = spawnLocations[1], seeableMapYS = y - 3, seeableMapYE = y + 4, seeableMapXS = x - 3, seeableMapXE = x + 4, points = 0;
	cats[0].x = spawnLocations[2], cats[0].y = spawnLocations[3], cats[1].x = spawnLocations[4], cats[1].y = spawnLocations[5]; // NPC startlocation.
	for (int i = 0; i < numbOfCats; i++)
		cats[i].lastMoved = 1;

	while (1) {
		if (points == 1200) {
			printf("Congratulations! You won!\nPoints earned: %d", points);
			getchar();
			break;
		}
		system("cls");
		moveMouse(map, &movement, &x, &y, &seeableMapYS, &seeableMapYE, &seeableMapXS, &seeableMapXE, &points);
		for (int i = 0; i < numbOfCats; i++) {
			NPCmovement(map, &cats[i].x, &cats[i].y, &points, &cats[i].lastMoved);
		}
	}
}