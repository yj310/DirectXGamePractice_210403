#pragma once
#include "player.h"
#include "global.h"

class GameSystem
{
public:

	GameSystem();
	Player* player;
	bool isSpace;

	int startX;
	int startY;

	int myLand;
	bool isFinish;

	void Update();
	void Render();
	void GetLand();
	void FloodFill();
	void EdgeUpdate();
	void DeleteTextures();

	int virtualMap[FLOOR_WIDTH * FLOOR_HEIGHT];

	LPDIRECT3DTEXTURE9* clearTex;
	LPD3DXSPRITE spr;

};