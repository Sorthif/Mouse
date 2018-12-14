void readMAP(char* filename, char arr[MAPSIZE][MAPSIZE]);
void printMapToFile(char* filename, char arr[MAPSIZE][MAPSIZE]);
void printHashtags();
void clearKorridor(char arr[MAPSIZE][MAPSIZE], int *x, int *y, int size);

//Run this in main to generate a map.
//Map will be stored in RandomMap.mp
void makeMap(int x, int y, int size, int nCats, int nCheeses);