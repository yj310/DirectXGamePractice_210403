#pragma once

class Player
{
public:
	
	Player();
	~Player();
	void Update();
	void Render();
	
	int posX;
	int posY;

	bool isSpace;

	LPDIRECT3DTEXTURE9* playerTex;
	LPD3DXSPRITE spr;

};