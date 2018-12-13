#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000
#define START_X 5
#define START_Y 5
#define EDGE 3

void readMAP(char* filename, char arr[SIZE][SIZE]);
void printMapToFile(char* filename, char arr[SIZE][SIZE]);
void printHashtags();
void clearKorridor(char arr[SIZE][SIZE], int *x, int *y, int size);

//Run this in main to generate a map.
//Map will be stored in RandomMap.mp
void makeMap(int x, int y, int size, int nCats, int nCheeses);