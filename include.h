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
#define WINDOW 5
#define EDGE WINDOW + 2

struct catBox {
	int numberOfCats;
	struct cat *cats;
};

struct cat {
	int x;
	int y;
	int lastMoved;
};
#endif