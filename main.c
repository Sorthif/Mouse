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

		//Kommenterar bort this now because Spawnlocations is not ready here
		//mouse pMouse = initMouse(spawnLocations);

		mouse pMouse;
		pMouse.pos.x = 5;
		pMouse.pos.y = 5;
		pMouse.poops = 0;
		
		mGame.playerMouse = &pMouse;
		makeMap(mGame);
		
		readMap("map.txt", map);
		int spawnLocations[100];
		getSpawnLocations(map, spawnLocations);
		allocateMemoryForCats(&litterBox, mLevel->nCats);

		initCats(&litterBox, mLevel->nCats, spawnLocations);

		//Deklarera Föstret
		// int windowWidth = WINDOW; //Uneccessary variable. It's already #defined
		window mainWindow = initWindow(WINDOW, pMouse);
		
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
	exit(0);
}