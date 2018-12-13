#ifdef __linux__ 
    #define GETCHARINPUT keypress(0)
#elif _WIN32
    #define GETCHARINPUT getche()
#else
#endif

#include <string.h>
#include <time.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

#define MAPSIZE 200
#define SIZE MAPSIZE
#define START_X 5
#define START_Y 5
#define EDGE 3
#define GETCHARINPUT keypress(0)

#include "map.h"