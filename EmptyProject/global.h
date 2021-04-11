#pragma once
#include "pageManager.h"


#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080


#define FLOOR_WIDTH 740
#define FLOOR_HEIGHT 932

#define	GAME_PAGE_X (WINDOW_WIDTH - FLOOR_WIDTH) / 2
#define GAME_PAGE_Y (WINDOW_HEIGHT - FLOOR_HEIGHT)



#define MAP_STATE_EMPTY 0
#define MAP_STATE_EDGE 1
#define MAP_STATE_VISITED 2
#define MAP_STATE_VISITING 3
#define MAP_STATE_VIRTUAL_EMPTY 4


struct Point
{
	int x;
	int y;
	Point(int x, int y)
		: x(x), y(y)
	{
	}
};


extern PageManager pageManager;


extern int floorP[FLOOR_WIDTH * FLOOR_HEIGHT];
extern int maskP[FLOOR_WIDTH * FLOOR_HEIGHT];
extern int mapP[FLOOR_WIDTH * FLOOR_HEIGHT];
extern int map[FLOOR_WIDTH * FLOOR_HEIGHT];