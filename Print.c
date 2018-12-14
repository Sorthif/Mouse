#include "include.h"

void printUI(int *points) {
	printf("\nPoints: %4d\n", *points);
}

void printWholeMap(char map[][MAPSIZE]) {
	for (int i = 0; i < MAPSIZE; i++) {
		printf("\n");
		for (int j = 0; j < MAPSIZE; j++)
			printf("%c", map[i][j]);
	}
}

void printSeeableMap(char map[][MAPSIZE], int ys, int ye, int xs, int xe) { // Y start, Y end, X start, X end.
	for (int i = ys; i < ye; i++) { // Y axis coordinates
		printf("\n");
		for (int j = xs; j < xe; j++) // X axis coordinates
			printf("%c", map[i][j]);
	}
	//printWholeMap(map); // Use when you need to print whole map.
}