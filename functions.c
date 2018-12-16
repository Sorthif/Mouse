#include "include.h"


void gameLost(char map[][MAPSIZE], int points) {
	CLEAR;
	printWholeMap(map);
	printf("\nYou lost!\nYou got %3d points!.", points);
	GETCHARINPUT;
}

int weightedDie(int lastmoved, int percentFwd, int percentLeft, int percentRight, int percentBack) {
	int percent = rand() % 100 + 1;
	if (percent <= percentFwd)
		return (lastmoved + 0) % 4;
	else if (percent <= percentFwd + percentLeft)
		return (lastmoved + 1) % 4;
	else if (percent <= percentFwd + percentLeft + percentRight)
		return (lastmoved + 3) % 4;
	else //Moves backwards.
		return (lastmoved + 2) % 4;
}

int randomMovementGenerator(int num1, int num2, int lastmoved) {
	int lower = num1, upper = num2;
	int num = (rand() % (upper - lower + 1)) + lower;
	return num;
}

void getSpawnLocations(char map[][MAPSIZE], int arr[20]) {
	int location = 0;
	for (int i = 0; i < MAPSIZE; i++) {
		for (int j = 0; j < MAPSIZE; j++) {
			if (map[i][j] == 'M') {
				arr[location] = j;
				arr[location + 1] = i;
				location = location + 2;
				break;
			}
			if (location == 2)
				break;
		}
	}
	for (int i = 0; i < MAPSIZE; i++) {
		for (int j = 0; j < MAPSIZE; j++) {
			if (map[i][j] == 'C') {
				arr[location] = j;
				arr[location + 1] = i;
				location = location + 2;
			}
		}
	}
}

