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

void printUI(game g) {
	printf("\nlevel: %d", g.currentLevel);
	printf("\nPoints: %4d/%4d %4d\tPoops: %2d/3\n", 
	g.levels[g.currentLevel-1].points, g.levels[g.currentLevel-1].winpoints, 
	g.totalPoints, g.playerMouse->poops);
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

void printLeaderboard(game g)
{
	char name[100];
	printf("\nEnter your name: ");
	scanf("%s", name);
	FILE* lf = fopen("leaderboard.txt", "a");
	fprintf(lf, "%s: %d points (level %d)\n", name, g.totalPoints, g.currentLevel);
	fclose(lf);
	lf = fopen("leaderboard.txt", "r");
	char c;
	printf("\n LEADERBOARD\n====================\n");
	while(!feof(lf))
	{
		fscanf(lf, "%c", &c);
		printf("%c", c);
	}
	fclose(lf);
}