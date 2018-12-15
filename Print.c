#include "include.h"

int isNotSecretCharacter(char c)
{
	char* poopChars = "2468";
	if(strchr(poopChars, c))
	{
		printf(".");
		return 0;
	}
	return 1;
}

void printUI(mouse m) {
	printf("\nPoints: %4d\tPoops: %2d\n", m.points, m.poops);
}

void printWholeMap(char map[][MAPSIZE]) {
	for (int i = 0; i < 50; i++) {
		printf("\n");
		for (int j = 0; j < 50; j++)
			printf("%c", map[i][j]);
	}
}

void printSeeableMap(char map[][MAPSIZE], int ys, int ye, int xs, int xe) { // Y start, Y end, X start, X end.
    for (int i = ys; i < ye; i++) { // Y axis coordinates
		printf("\n");
		for (int j = xs; j < xe; j++) // X axis coordinates
			if(isNotSecretCharacter(map[i][j]))
			{
				printf("%c", map[i][j]);
			}
	}
	//printWholeMap(map); // Use when you need to print whole map.
}
