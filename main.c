#include "include.h"

int main(void) {
	int lifeStatus = alive;
	int turns = 0;
	int movement = stayed;

	char input;
	char map[MAPSIZE][MAPSIZE];

	game mGame;
	srand(time(0));
	generateLevels(10, &mGame);

	/*===============LEVELS LOOP==============*/
	while(lifeStatus == alive) { 
		int spawnLocations[100];
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
		getSpawnLocations(map, spawnLocations);
		
		allocateMemoryForCats(&litterBox, mLevel->nCats);
		initCats(&litterBox, mLevel->nCats, spawnLocations);

		//Deklarera Föstret
		int windowWidth = WINDOW; //Uneccessary variable. It's already #defined
		window mainWindow = initWindow(WINDOW, pMouse);
		
		CLEAR;

		/*==============GAME LOOP=================*/
		while (lifeStatus == alive) { //Will loop while alive
			if (mLevel->points >= mLevel->winpoints) {
				printf("Congratulations! You beat the level!\nPoints earned: %d", mLevel->points);
				getchar();
				break;
			}
	
			printSeeableMap(map, mainWindow.y.start, mainWindow.y.end, mainWindow.x.start, mainWindow.x.end);
			printUI(mGame);

			do { //Will loop when trying to walk into a wall

				input = GETCHARINPUT;
				movement = moveMouse(map, &mGame, &mainWindow, input);
			} while(movement == stayed);

			CLEAR;

			if (movement == dead) {
				lifeStatus = dead;
			}
			else {
				lifeStatus = moveCats(map, mGame.levels, &litterBox);
			}

			turns++;
		}
		free(litterBox.cats);
		if (mGame.currentLevel < mGame.nLevels && lifeStatus == alive)
		{
			mGame.currentLevel++;
		} else {
			printf("All %d levels completed\n", mGame.nLevels);
			break; //GAME WON ALL LEVELS!!
		}
	}

	/*================GAME ENDED==============*/
	gameLost(map, mGame.totalPoints);
	printLeaderboard(mGame);
	return 0;
}