#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000
#define START_X 5
#define START_Y 5
#define EDGE 3

/*======================= READ ===========================================*/
void readMAP(char* filename, char arr[SIZE][SIZE])
{
    FILE* f = fopen(filename, "r");
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            arr[i][j] = fgetc(f);
        }
        fgetc(f);
    }
    fclose(f);
}

/*======================= PRINT ===========================================*/
void printMapToFile(char* filename, char arr[SIZE][SIZE])
{
    FILE* f = fopen(filename, "w");
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            fputc(arr[i][j], f);
        }
        if(i != SIZE - 1)
            fputc('\n', f);
    }
    fclose(f);
}

void printHashtags()
{
    FILE* f = fopen("hashtagmap.mp", "w");
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            fputc('#', f);
        }
        if(i != SIZE - 1)
            fputc('\n', f);
    }
    fclose(f);
}
/*======================= RAND ===========================================*/


/*======================= CLEAR ===========================================*/

void clearKorridor(char arr[SIZE][SIZE], int *x, int *y, int size)
{
    int dir = rand() % 2;
    int l1, l2;
    int i, j;
    do{
        if(dir)
        {
            l1 = 1;//rand() % 2 + 1; //Width of corridor
            l2 = rand() % 10 + 5; //Length of Corridor
        }else
        {
            l2 = 1;//rand() % 2 + 1; //Width of corridor
            l1 = rand() % 10 + 5; //Length of Corridor
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

int main()
{
    int x = 5, y = 5;
    int size = 100;
    int nKorridors = size * 2;
    int nCats = 5;
    int nCheeses = 10;
    srand(time(0));
    char arr[SIZE][SIZE];
    printHashtags();
    readMAP("hashtagmap.mp", arr);
    arr[x][y] = 'M';
    for(int i = 0; i < nKorridors; i++)
    {
        //getchar();
        clearKorridor(arr, &x, &y, size);
        if(i % (nKorridors / nCats) == 1)
        {
            arr[x][y] = 'C';
        }
        if(i % (nKorridors / nCheeses) ==2)
        {
            arr[x][y] = 'o';
        }
    }
    printMapToFile("printedmap.mp", arr);
}