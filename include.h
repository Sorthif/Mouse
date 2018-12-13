#ifdef __linux__ 
    #define GETCHARINPUT keypress(0)
	#include <termios.h>
	#include <unistd.h>
#elif _WIN32
    #define GETCHARINPUT getche()
#else
#endif

#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define MAPSIZE 200
#define SIZE MAPSIZE
#define START_X 5
#define START_Y 5
#define EDGE 3


#include "map.h"

struct cat {
	int x;
	int y;
	int lastMoved;
};