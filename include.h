#ifndef INCLUDE
#define INCLUDE

#ifdef __linux__ 
	#define KEYPRESS_DECLARATION int keypress(unsigned char echo)
    #define GETCHARINPUT keypress(0)
	#define CLEAR system("clear")
	#include <termios.h>
	#include <unistd.h>
#elif _WIN32
	#define KEYPRESS_DECLARATION 1+1
    #define GETCHARINPUT getch()
	#define CLEAR system("cls")
#else
#endif

#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define MAPSIZE 200
#define START_X 5
#define START_Y 5
#define WINDOW 7
#define EDGE WINDOW + 2
#define AMOUNTOFCATS 5
#define MAXPOOPS 3

struct catBox {
	int numberOfCats;
	struct cat *cats;
};

struct cat {
	int x;
	int y;
	int lastMoved;
	int foundPoop;
};

//Coordinates for an abject such as mouse
typedef struct coor {
	int x;
	int y;
} coor;

//A mouuse, used for the player character
typedef struct mouse {
	struct coor pos;
	int poops;
	char direction;
} mouse;

//Used in struct window and represents a line between two positions
typedef struct line {
	int start;
	int end;
} line;

typedef struct window {
	//Contains the limits for the current view drawn in the terminal
	line y;
	line x;
} window;

//contains all information needed to keep track of in the range of a level
typedef struct level {
	int size;
	int points;
	int winpoints;
	int nCheeses;
	int nCats;
	int seed;
} level;


//contains all levels as an array and variables for things that is kept the whole game
typedef struct game {
	struct level* levels;
	int currentLevel;
	int totalPoints;
	int nLevels;
	struct mouse* playerMouse;
} game;

enum statuses {dead = 0, walked, stayed, alive, blocked};

// INIT
mouse initMouse();
window initWindow(int windowWidth, mouse pMouse);
void initCats(struct catBox *litterBox, int amount);
void generateLevels(int nLevels, game* g);
void allocateMemoryForCats(struct catBox *litterBox, int numberOfCats);

// FUNCTIONS
void gameLost(char map[][MAPSIZE], int points);
int weightedDie(int lastmoved, int percentFwd, int percentLeft, int percentRight, int percentBack);
int randomMovementGenerator(int num1, int num2, int lastmoved);

// CATS
int NPCmovement(char map[][MAPSIZE], struct cat *c, int *points);
int moveCats(char map[][MAPSIZE], level *mLevel, struct catBox *litterBox);

// PRINT
int isNotSecretCharacter(char c);
void printUI(game g);
void printWholeMap(char map[][MAPSIZE]);
void printSeeableMap(char map[][MAPSIZE], int ys, int ye, int xs, int xe);
void printLeaderboard(game g);

// MAIN

// MOUSE
void poop(char map[][MAPSIZE], mouse* m);
int moveMouse(char map[][MAPSIZE], game* g, window* w, int input);

// RANDOM MAP
void readMap(char* filename, char arr[MAPSIZE][MAPSIZE]);
void printMapToFile(char* filename, char arr[MAPSIZE][MAPSIZE]);
void printHashtags();
void clearKorridor(char arr[MAPSIZE][MAPSIZE], int *x, int *y, int size);
void clearBonus(char arr[MAPSIZE][MAPSIZE], int *x, int *y, int size);
void makeMap(game g);

// KEYPRESS
//KEYPRESS_DECLARATION;

#endif