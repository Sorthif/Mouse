#include "include.h"
void poop(char map[][MAPSIZE], mouse* m)
{
    int x = 0, y = 0;
    switch(m->direction)
    {
        case 'a': //LEFT
            map[m->pos.y][m->pos.x + 1] = '4';
            break;
        case 's': //DOWN
            map[m->pos.y -1][m->pos.x] = '2';
            break; 
        case 'w': //UP
            map[m->pos.y + 1][m->pos.x] = '8';
            break;
        case 'd': //RIGHT
            map[m->pos.y][m->pos.x - 1] = '6';

    }
    (m->poops)--;
}

static void helpMoveMouse(mouse *m, window *w, int x, int y){
    if (x){
        m->pos.x += x;
        w->x.start += x;
        w->x.end += x;
    }
    else if (y){
        m->pos.y += y;
        w->y.start += y;
        w->y.end += y;
    }
}

int moveMouse(char map[][MAPSIZE], game* g, window* w) {
	mouse* m = g->playerMouse;
    char *pCurPos = &map[m->pos.y][m->pos.x];
	if(m->direction == 'a' && map[m->pos.y][m->pos.x - 1] != '#')//LEFT
    {
        *pCurPos = ' ';
        helpMoveMouse(m, w, -1, 0);
    }
	else if(m->direction == 's' && map[m->pos.y + 1][m->pos.x] != '#')//DOWN
    {
		*pCurPos = ' ';
        helpMoveMouse(m, w, 0, 1);
    }
	else if(m->direction == 'w' && map[m->pos.y - 1][m->pos.x] != '#') //UP
    {
		*pCurPos = ' ';
        helpMoveMouse(m, w, 0, -1);
    }
    else if(m->direction == 'd' && map[m->pos.y][m->pos.x + 1] != '#') //RIGHT
	{
		*pCurPos = ' ';
        helpMoveMouse(m, w, 1, 0);
	} else
    {
        return 2; //Gick inte att gå i någon riktning
    }

    pCurPos = &map[m->pos.y][m->pos.x]; //Uppdatera till nya positionen
    if(*pCurPos == 'o') 
    {
		g->levels[g->currentLevel-1].points = g->levels[g->currentLevel-1].points + 100;
        g->totalPoints += 100;
        if(m->poops < MAXPOOPS) 
        {
            m->poops++;
        } else
        {
            poop(map, m);
        }
    } else if (*pCurPos == 'C') 
    {
        return 0; //GAME LOST
    }
    *pCurPos = 'M';
    return 1;
}