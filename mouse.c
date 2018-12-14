#include "include.h"

int moveMouse(char map[][MAPSIZE], mouse* m, window* w) {
    printSeeableMap(map, w->y.start, w->y.end, w->x.start, w->x.end);

    char *pCurPos = &map[m->pos.y][m->pos.x];
	printUI(m->points);
	char direction = GETCHARINPUT;
	//switch (direction) {
	if(direction == 'a' && map[m->pos.y][m->pos.x - 1] != '#')//LEFT
    {
        *pCurPos = ' ';
        (m->pos.x)--;
		(w->x.start)--;
		(w->x.end)--;
    }
	else if(direction == 's' && map[m->pos.y + 1][m->pos.x] != '#')//DOWN
    {
		*pCurPos = ' ';
		(m->pos.y)++;
		(w->y.start)++;
		(w->y.end)++;
    }
	else if(direction == 'w' && map[m->pos.y - 1][m->pos.x] != '#') //UP
    {
		*pCurPos = ' ';
		(m->pos.y)--;
		(w->y.start)--;
		(w->y.end)--;
    }
    else if(direction == 'd' && map[m->pos.y][m->pos.x + 1] != '#') //RIGHT
	{
		*pCurPos = ' ';
		(m->pos.x)++;
		(w->x.start)++;
		(w->x.end)++;
	} else
    {
        return 1; //Gick inte att gå i någon riktning
    }

    pCurPos = &map[m->pos.y][m->pos.x]; //Uppdatera till nya positionen
    if(*pCurPos == 'o') 
    {
			m->points = m->points + 100;
    } else if (*pCurPos == 'C') 
    {
        return 0; //GAME LOST
    }
    *pCurPos = 'M';
    return 1;
}