#include "include.h"

int moveMouse(char map[][MAPSIZE], char *movement, int *x, int *y, int *ys, int *ye, int *xs, int *xe, int *points) {
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
			return 0; //GAME LOST
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
			return 0; //GAME LOST
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
			return 0; //GAME LOST
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
			return 0; //GAME LOST
		}
		(*xs)++;
		(*xe)++;
		map[*y][*x] = 'M';
		break;
	}
    return 1;
}