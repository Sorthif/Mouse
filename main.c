#include "include.h"

int main(void) {
	int lost = 0, turns = 0;
	char input;

	char map[MAPSIZE][MAPSIZE];

	game mGame;
	srand(time(0));
	generateLevels(10, &mGame);

	while(!lost)
	{
		level *mLevel = &(mGame.levels[mGame.currentLevel-1]);
		struct catBox litterBox;

		//deklarera musen
		mouse pMouse;
		pMouse.pos.x = 5;
		pMouse.pos.y = 5;
		pMouse.poops = 0;
		
		mGame.playerMouse = &pMouse;
		makeMap(mGame);
		
		readMap("RandomMap.mp", map);
		int spawnLocations[100];
		getSpawnLocations(map, spawnLocations);
		allocateMemoryForCats(&litterBox, mLevel->nCats);

		for (int i = 2, j = 3, k = 0; k < mLevel->nCats; i = i + 2, j = j + 2, k++) {
			litterBox.cats[k].lastMoved = 1;
			litterBox.cats[k].x = spawnLocations[i];
			litterBox.cats[k].y = spawnLocations[j];
		}

		//Deklarera Föstret
		int windowWidth = WINDOW;
		window mainWindow;
		mainWindow.x.start = pMouse.pos.x - windowWidth;
		mainWindow.x.end = pMouse.pos.x + windowWidth + 1;
		mainWindow.y.start = pMouse.pos.y - windowWidth;
		mainWindow.y.end = pMouse.pos.y + windowWidth + 1;

		CLEAR;
		while (!lost) {
			if (mLevel->points == mLevel->winpoints) {
				printf("Congratulations! You beat the level!\nPoints earned: %d", mLevel->points);
				getchar();
				break;
			}
			int walked = 2;
			while(walked == 2)
			{
				printSeeableMap(map, mainWindow.y.start, mainWindow.y.end, mainWindow.x.start, mainWindow.x.end);
				printUI(mGame);
				input = GETCHARINPUT;
				CLEAR;
				if(input == ' ')
				{
					break;
				} else if(input == 'p' && pMouse.poops > 0)
				{
					poop(map, &pMouse);
					break;
				}
				pMouse.direction = input;
				walked = moveMouse(map, &mGame, &mainWindow);
				if(walked == 0)
				{
					lost = 1;
				}
			}

			for (int i = 0; i < mLevel->nCats; i++) {
				if(!NPCmovement(map, &litterBox.cats[i], &mLevel->points))
				{
					lost = 1;
				}
			}
			turns++;
			
		}
		free(litterBox.cats);
		if(mGame.currentLevel < mGame.nLevels && !lost)
		{
			mGame.currentLevel++;
		}else{
			break; //GAME WON ALL LEVELS!!
		}
	}
	gameLost(map, mGame.totalPoints);
	printLeaderboard(mGame);
	exit(1);
}