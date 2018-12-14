#include "include.h"


void buildMapLevel1(char map[][MAPSIZE]) {
	FILE *fp;
	fp = fopen("RandomMap.mp", "r");
	if (fp == NULL)
		exit(1);

	for (int i = 0; i < MAPSIZE; i++) {
		for (int j = 0; j < MAPSIZE; j++) {
			fscanf(fp, "%c", &map[i][j]);
		}
		fgetc(fp);
	}
	fclose(fp);
}

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

void gameLost(char map[][MAPSIZE], int points) {
	CLEAR;
	//printWholeMap(map);
	printf("\nYou lost!\nYou got %3d points!.", points);
	getchar();
	exit(1);
}

void moveMouse(char map[][MAPSIZE], char *movement, int *x, int *y, int *ys, int *ye, int *xs, int *xe, int *points) {
	printSeeableMap(map, *ys, *ye, *xs, *xe);
	printUI(points);
	*movement = GETCHARINPUT;
	switch (*movement) {
	case 'a':
		if (map[*y][*x - 1] == '#') {
			break;
		}
		map[*y][*x] = ' ';
		(*x)--;
		if (map[*y][*x] == 'o')
			*points = *points + 100;
		if (map[*y][*x] == 'C') {
			gameLost(map, *points);
		}
		(*xs)--;
		(*xe)--;
		map[*y][*x] = 'M';
		break;
	case 's':
		if (map[*y + 1][*x] == '#') {
			break;
		}
		map[*y][*x] = ' ';
		(*y)++;
		if (map[*y][*x] == 'o')
			*points = *points + 100;
		if (map[*y][*x] == 'C') {
			gameLost(map, *points);
		}
		(*ys)++;
		(*ye)++;
		map[*y][*x] = 'M';
		break;
	case 'w':
		if (map[*y - 1][*x] == '#') {
			break;
		}
		map[*y][*x] = ' ';
		(*y)--;
		if (map[*y][*x] == 'o')
			*points = *points + 100;
		if (map[*y][*x] == 'C') {
			gameLost(map, *points);
		}
		(*ys)--;
		(*ye)--;
		map[*y][*x] = 'M';
		break;
	case 'd':
		if (map[*y][*x + 1] == '#') {
			break;
		}
		map[*y][*x] = ' ';
		(*x)++;
		if (map[*y][*x] == 'o')
			*points = *points + 100;
		if (map[*y][*x] == 'C') {
			gameLost(map, *points);
		}
		(*xs)++;
		(*xe)++;	
		map[*y][*x] = 'M';
		break;
	}
}

int randomMovementGenerator(int num1, int num2, int lastmoved) {
	int lower = num1, upper = num2;
	int num = (rand() % (upper - lower + 1)) + lower;

	return num;
}

void NPCmovement(char map[][MAPSIZE], int *x, int *y, int *points, int *lastMoved) {
	_Bool moveSuccessfull = 0, checkLastMoved = 0;
	int movement; 
	while (moveSuccessfull == 0) {
		if (checkLastMoved == 0) {
			movement = *lastMoved;
		}
		else
			movement = randomMovementGenerator(1, 4, *lastMoved);
		switch (movement) {
		case 1: // Left
			if (map[*y][*x - 1] == '#') {
				checkLastMoved = 1;
				break;
			}
			if (map[*y][*x - 1] == 'o') {
				checkLastMoved = 1;
				break;
			}
			map[*y][*x] = ' ';
			(*x)--;
			if (map[*y][*x] == 'M') {
				gameLost(map, *points);
			}
			map[*y][*x] = 'C';
			moveSuccessfull = 1;
			*lastMoved = 1;
			break;
		case 2: // Down
			if (map[*y + 1][*x] == '#') {
				checkLastMoved = 1;
				break;
			}
			if (map[*y + 1][*x] == 'o') {
				checkLastMoved = 1;
				break;
			}
			map[*y][*x] = ' ';
			(*y)++;
			if (map[*y][*x] == 'M') {
				gameLost(map, *points);
			}
			map[*y][*x] = 'C';
			moveSuccessfull = 1;
			*lastMoved = 2;
			break;
		case 3: // Up
			if (map[*y - 1][*x] == '#') {
				checkLastMoved = 1;
				break;
			}
			if (map[*y - 1][*x] == 'o') {
				checkLastMoved = 1;
				break;
			}
			map[*y][*x] = ' ';
			(*y)--;
			if (map[*y][*x] == 'M') {
				gameLost(map, *points);
			}
			map[*y][*x] = 'C';
			moveSuccessfull = 1;
			*lastMoved = 3;
			break;
		case 4: // Right
			if (map[*y][*x + 1] == '#') {
				checkLastMoved = 1;
				break;
			}
			if (map[*y][*x + 1] == 'o') {
				checkLastMoved = 1;
				break;
			}
			map[*y][*x] = ' ';
			(*x)++;
			if (map[*y][*x] == 'M') {
				gameLost(map, *points);
			}
			map[*y][*x] = 'C';
			moveSuccessfull = 1;
			*lastMoved = 4;
			break;
		}
	}
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

