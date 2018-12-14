#include "include.h"

int moveMouse(char map[][MAPSIZE], int *x, int *y, window* w, int *points) {
    printSeeableMap(map, w->y.start, w->y.end, w->x.start, w->x.end);


	printUI(points);
	char direction = GETCHARINPUT;
	switch (direction) {
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
		(w->x.start)--;
		(w->x.end)--;
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
		(w->y.start)++;
		(w->y.end)++;
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
		(w->y.start)--;
		(w->y.end)--;
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
		(w->x.start)++;
		(w->x.end)++;
		map[*y][*x] = 'M';
		break;
	}
    return 1;
}