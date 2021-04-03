#pragma once
#include "player.h"

class GameSystem
{
public:

	GameSystem();
	Player* player;

	void Update();
	void Render();
	void DeleteTextures();

};