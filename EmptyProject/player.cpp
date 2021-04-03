#include "DXUT.h"
#include "player.h"
#include "global.h"


Player::Player()
{
	posX = 0;
	posY = 0;
	isSpace = false;

	playerTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/player.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0
		, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0
		, nullptr
		, nullptr
		, playerTex
	);



	D3DXCreateSprite(DXUTGetD3D9Device(), &spr);

}

Player::~Player()
{
	(*playerTex)->Release();
	spr->Release();

}


void Player::Update()
{

	isSpace = false;
	if ((GetAsyncKeyState(VK_SPACE) & 0x8000) != 0)
		isSpace = true;

	if ((GetAsyncKeyState(VK_LEFT) & 0x8000) != 0)
	{
		
		if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_EDGE
			&& map[posY * FLOOR_WIDTH + (posX - 1)] == MAP_STATE_EDGE)
		{
			if(posX - 1 >= 0)
				posX -= 1;
		}

		if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_EDGE
			&& map[posY * FLOOR_WIDTH + (posX - 1)] == MAP_STATE_EMPTY
			&& isSpace)
		{
			posX -= 1;
			map[posY * FLOOR_WIDTH + posX] = MAP_STATE_VISITING;
		}

		if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_VISITING
			&& map[posY * FLOOR_WIDTH + (posX - 1)] == MAP_STATE_EMPTY)
		{
			posX -= 1;
			map[posY * FLOOR_WIDTH + posX] = MAP_STATE_VISITING;
		}

		if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_VISITING
			&& map[posY * FLOOR_WIDTH + (posX - 1)] == MAP_STATE_EDGE)
		{
			posX -= 1;
			// get rend
		}
		
	}
	else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0)
	{
		if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_EDGE
			&& map[posY * FLOOR_WIDTH + (posX + 1)] == MAP_STATE_EDGE)
		{
			if(posX + 1 < FLOOR_WIDTH)
				posX += 1;
		}

		if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_EDGE
			&& map[posY * FLOOR_WIDTH + (posX + 1)] == MAP_STATE_EMPTY
			&& isSpace)
		{
			posX += 1;;
			map[posY * FLOOR_WIDTH + posX] = MAP_STATE_VISITING;
		}

		if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_VISITING
			&& map[posY * FLOOR_WIDTH + (posX + 1)] == MAP_STATE_EMPTY)
		{
			posX += 1;
			map[posY * FLOOR_WIDTH + posX] = MAP_STATE_VISITING;
		}
		if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_VISITING
			&& map[posY * FLOOR_WIDTH + (posX + 1)] == MAP_STATE_EDGE)
		{
			posX += 1;
			// get rend
		}
		
	}
	else if ((GetAsyncKeyState(VK_UP) & 0x8000) != 0)
	{
		if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_EDGE
			&& map[(posY - 1) * FLOOR_WIDTH + posX] == MAP_STATE_EDGE)
		{
			if(posY - 1 >= 0)
				posY -= 1;
		}

		if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_EDGE
			&& map[(posY - 1) * FLOOR_WIDTH + posX] == MAP_STATE_EMPTY
			&& isSpace)
		{
			posY -= 1;
			map[posY * FLOOR_WIDTH + posX] = MAP_STATE_VISITING;
		}

		if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_VISITING
			&& map[(posY - 1) * FLOOR_WIDTH + posX] == MAP_STATE_EMPTY)
		{
			posY -= 1;
			map[posY * FLOOR_WIDTH + posX] = MAP_STATE_VISITING;
		}

		if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_VISITING
			&& map[(posY - 1) * FLOOR_WIDTH + posX] == MAP_STATE_EDGE)
		{
			posY -= 1;
			// get rend
		}
	}
	else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) != 0)
	{
		if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_EDGE
			&& map[(posY + 1) * FLOOR_WIDTH + posX] == MAP_STATE_EDGE)
		{
			if(posX + 1 < FLOOR_HEIGHT)
				posY += 1;
		}

		if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_EDGE
			&& map[(posY + 1) * FLOOR_WIDTH + posX] == MAP_STATE_EMPTY
			&& isSpace)
		{
			posY += 1;
			map[posY * FLOOR_WIDTH + posX] = MAP_STATE_VISITING;
		}

		if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_VISITING
			&& map[(posY + 1) * FLOOR_WIDTH + posX] == MAP_STATE_EMPTY)
		{
			posY += 1;
			map[posY * FLOOR_WIDTH + posX] = MAP_STATE_VISITING;
		}

		if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_VISITING
			&& map[(posY + 1) * FLOOR_WIDTH + posX] == MAP_STATE_EDGE)
		{
			posY += 1;
			// get rend
		}
	}
}

void Player::Render()
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 cen;

	spr->Begin(D3DXSPRITE_ALPHABLEND);

	pos = { (float)GAME_PAGE_X + posX, (float)GAME_PAGE_Y + posY, 0 };
	cen = { 2, 2, 0 };

	spr->Draw(*playerTex, nullptr, &cen, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));


	spr->End();
}