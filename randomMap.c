#include "include.h"

/*======================= READ ===========================================*/
void readMap(char* filename, char arr[MAPSIZE][MAPSIZE])
{
    FILE* f = fopen(filename, "r");
    for(int i = 0; i < MAPSIZE; i++)
    {
        for(int j = 0; j < MAPSIZE; j++)
        {
            arr[i][j] = fgetc(f);
        }
        fgetc(f);
    }
    fclose(f);
}

/*======================= PRINT ===========================================*/
void printMapToFile(char* filename, char arr[MAPSIZE][MAPSIZE])
{
    FILE* f = fopen(filename, "w");
    for(int i = 0; i < MAPSIZE; i++)
    {
        for(int j = 0; j < MAPSIZE; j++)
        {
            fputc(arr[i][j], f);
        }
        if(i != MAPSIZE - 1)
            fputc('\n', f);
    }
    fclose(f);
}

void printHashtags()
{
    FILE* f = fopen("RandomMap.mp", "w");
    for(int i = 0; i < MAPSIZE; i++)
    {
        for(int j = 0; j < MAPSIZE; j++)
        {
            fputc('#', f);
        }
        if(i != MAPSIZE - 1)
            fputc('\n', f);
    }
    fclose(f);
}
/*======================= RAND ===========================================*/


/*======================= CLEAR ===========================================*/

void clearKorridor(char arr[MAPSIZE][MAPSIZE], int *x, int *y, int size)
{
    int dir = rand() % 2;
    int l1, l2;
    int i, j;
    do{
        if(dir)
        {
            l1 = 1;//rand() % 2 + 1; //Width of corridor
            l2 = rand() % 5 + 3; //Length of Corridor
        }else
        {
            l2 = 1;//rand() % 2 + 1; //Width of corridor
            l1 = rand() % 5 + 3; //Length of Corridor
        }
    }while(*x + l1 > size - EDGE && *y + l2 > size - EDGE);

    dir = rand() % 2;

    if(dir || *x - l1 < EDGE || *y - l2 < EDGE)
    {
        for(i = *x; i < *x + l1; i++)
        {
            for(j = *y; j < *y + l2; j++)
            {
                if(arr[i][j] == '#')
                {
                    arr[i][j] = ' ';
                }
            }
        }
        *x = i-1;
        *y = j-1;
    }else
    {
        for(i = *x; i > *x - l1; i--)
        {
            for(j = *y; j > *y - l2; j--)
            {
                if(arr[i][j] == '#')
                {
                    arr[i][j] = ' ';
                }
            }
        }
        *x = i+1;
        *y = j+1;
    }
}

void clearBonus(char arr[MAPSIZE][MAPSIZE], int *x, int *y, int size)
{
    char* str = "      ### ##    ##  # ##    ##### ####  #### #####   ### # ### # ###   ### # ###   #### ####  #### #####o##### ##### #####C#####o####oooo#######";
    for(int i = 0; i < 10; i++)
    {
        arr[*y][*x + i] = ' '; //Rita en korridor till h;ger
    }
    int len = strlen(str);
    for(int i = 0; i < len / 6; i++)
    {
        for(int j = 10; j < 16; j++)
        {
            arr[*y+i][*x+j] = *str;
            str = str+1;
        }
    }
}

void makeMap(game g)
{
    
    int x = g.playerMouse->pos.x;
    int y = g.playerMouse->pos.y;
    int size = g.levels[g.currentLevel-1].size;
    int nCats = g.levels[g.currentLevel-1].nCats;
    int nCheeses = g.levels[g.currentLevel-1].nCheeses;
    int nKorridors = size * 2;
    srand(g.levels[g.currentLevel-1].seed);
    char arr[MAPSIZE][MAPSIZE];
    printHashtags();
    readMap("RandomMap.mp", arr);
    arr[x][y] = 'M';
    
    for(int i = 0; i < nKorridors; i++)
    {
        //getchar();
        clearKorridor(arr, &x, &y, size);
        
        if(i % (nKorridors / nCats) == 10)
        {
            arr[x][y] = 'C';
        }else if(i % (nKorridors / nCheeses) == 2)
        {
            arr[x][y] = 'o';
        }else if(i == nKorridors - 2)
        {
            clearBonus(arr, &x, &y, size);
        }
    }

    printMapToFile("RandomMap.mp", arr);
}