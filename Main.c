#include <stdio.h>
#include <string.h>;
#define MAPSIZE 22

void buildMapLevel1(char map[][MAPSIZE]) {
	FILE *fp;
	fp = fopen("Level1.txt", "r");
	if (fp == NULL)
		exit(1);

	for (int i = 0; i < MAPSIZE; i++) {
		for (int j = 0; j <= MAPSIZE; j++) {
			fscanf(fp, "%c", &map[i][j]);
		}
	}
	fp = fclose;
}
void printUI(int *points) {
	printf("\nPoints: %4d\n", *points);
}

void printSeeableMap(char map[][MAPSIZE], int *ys, int *ye, int *xs, int *xe) { // Y start, Y end, X start, X end.
	for (int i = *ys; i < *ye; i++) { // Y axis coordinates
		printf("\n");
		for (int j = *xs; j < *xe; j++) // X axis coordinates
			printf("%c", map[i][j]);
	}
	//printf("\n");
	//for (int i = 0; i < MAPSIZE; i++) { 
	//	printf("\n");
	//	for (int j = 0; j < MAPSIZE; j++) // Use when you need to print whole map.
	//		printf("%c", map[i][j]);
	//}
}

void moveMouse(char map[][MAPSIZE], char *movement, int *x, int *y, int *ys, int *ye, int *xs, int *xe, int *points) {
	printSeeableMap(map, ys, ye, xs, xe);
	printUI(points);
	*movement = getche();
	switch (*movement) {
	case 'a':
		if (map[*y][*x - 1] == '#') {
			break;
		}
		map[*y][*x] = ' ';
		(*x)--;
		if (map[*y][*x] == 'o')
			*points = *points + 100;
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
		(*xs)++;
		(*xe)++;	
		map[*y][*x] = 'M';
		break;
	}
}
// Implement random movement!
void NPCmovement(char map[][MAPSIZE], int *x, int *y) {
	int movement;
	switch (movement) {
	case '1':
		if (map[*y][*x - 1] == '#') {
			break;
		}
		map[*y][*x] = ' ';
		(*x)--;
		if (map[*y][*x] == 'M') {

		}
		map[*y][*x] = 'C';
		break;
	case '2':
		if (map[*y + 1][*x] == '#') {
			break;
		}
		map[*y][*x] = ' ';
		(*y)++;
		if (map[*y][*x] == 'M') {

		}
		map[*y][*x] = 'C';
		break;
	case '3':
		if (map[*y - 1][*x] == '#') {
			break;
		}
		map[*y][*x] = ' ';
		(*y)--;
		if (map[*y][*x] == 'M') {

		}
		map[*y][*x] = 'C';
		break;
	case '4':
		if (map[*y][*x + 1] == '#') {
			break;
		}
		map[*y][*x] = ' ';
		(*x)++;
		if (map[*y][*x] == 'M') {

		}
		map[*y][*x] = 'C';
		break;
	}
}


int main(void) {

	char map[MAPSIZE][MAPSIZE], *movement = 's';

	buildMapLevel1(&map);
	
	int x = 5, y = 5, seeableMapYS = 3, seeableMapYE = 8, seeableMapXS = 3, seeableMapXE = 8, points = 0;
	int AI1X = 13, AI1Y = 8, AI2X = 7, AI2Y = 15; // NPC startlocation.
	map[y][x] = 'M'; // Mouse startlocation.
	map[AI1Y][AI1X] = 'C', map[AI2Y][AI2X] = 'C';
	while (1) {
		if (points == 800) {
			printf("Congratulations! You won!\nPoints earned: %d", points);
			getch();
			break;
		}
		system("cls");
		moveMouse(&map, &movement, &x, &y, &seeableMapYS, &seeableMapYE, &seeableMapXS, &seeableMapXE, &points);
	/*	NPCmovement(&map, &AI1X, &AI1Y);
		NPCmovement(&map, &AI2X, &AI2Y);*/
	}


}