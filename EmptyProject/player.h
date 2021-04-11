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


	LPDIRECT3DTEXTURE9* playerTex;
	LPD3DXSPRITE spr;




	D3DXVECTOR2 getPos() {
		return { (float)posX, (float)posY };
	}
	

	void move(D3DXVECTOR2 dir) {
		posX += dir.x;
		posY += dir.y;
	}

};