#ifndef INCLUDE
#define INCLUDE

#ifdef __linux__ 
    #define GETCHARINPUT keypress(0)
	#define CLEAR system("clear")
	#include <termios.h>
	#include <unistd.h>
#elif _WIN32
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

struct catBox {
	int numberOfCats;
	struct cat *cats;
};

struct cat {
	int x;
	int y;
	int lastMoved;
};

typedef struct coor {
	int x;
	int y;
} coor;

typedef struct mouse {
	coor pos;
	int points;
	char direction;
} mouse;

typedef struct line {
	int start;
	int end;
} line;

typedef struct window {
	//Contains the limits for the current view drawn in the terminal
	line y;
	line x;
} window;

#endif