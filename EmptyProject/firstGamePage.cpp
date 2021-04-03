#include "DXUT.h"
#include "global.h"
#include "firstGamePage.h"


FirstGamePage::FirstGamePage()
{

	backgroundTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/background.png"
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
		, backgroundTex);

	floorTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/floor.png"
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
		, floorTex);

	maskTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/mask.png"
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
		, maskTex);


	D3DLOCKED_RECT lr;
	RECT rt = {0, 0,  FLOOR_WIDTH, FLOOR_HEIGHT };
  	if (SUCCEEDED((*floorTex)->LockRect(0, &lr, &rt, 0)))
	{
		DWORD* p = (DWORD*)lr.pBits;
		memcpy(floorP, p, FLOOR_WIDTH * FLOOR_HEIGHT * 4);
		(*floorTex)->UnlockRect(0);
	}

	if (SUCCEEDED((*maskTex)->LockRect(0, &lr, &rt, 0)))
	{
		DWORD* p = (DWORD*)lr.pBits;
		memcpy(maskP, p, FLOOR_WIDTH * FLOOR_HEIGHT * 4);
		(*maskTex)->UnlockRect(0);
	}

	
	for (int i = 0; i < FLOOR_WIDTH * FLOOR_HEIGHT; i++)
	{
		map[i] = MAP_STATE_EMPTY;
	}
	for (int y = 0; y < FLOOR_HEIGHT; y++)
	{
		map[y * FLOOR_WIDTH + 0] = MAP_STATE_EDGE;
		map[y * FLOOR_WIDTH + FLOOR_WIDTH - 1] = MAP_STATE_EDGE;
	}
	for (int x = 0; x < FLOOR_WIDTH; x++)
	{
		map[0 * FLOOR_WIDTH + x] = MAP_STATE_EDGE;
		map[(FLOOR_HEIGHT - 1) * FLOOR_WIDTH + x] = MAP_STATE_EDGE;
	}

	MapUpdate();


	D3DXCreateSprite(DXUTGetD3D9Device(), &spr);


}

FirstGamePage::~FirstGamePage()
{
	(*floorTex)->Release();
	(*maskTex)->Release();
	(*backgroundTex)->Release();
	spr->Release();
	gameSystem.DeleteTextures();
}


void FirstGamePage::MapUpdate()
{
	D3DLOCKED_RECT lr;
	RECT rt = { 0, 0,  FLOOR_WIDTH, FLOOR_HEIGHT };

	if (SUCCEEDED((*floorTex)->LockRect(0, &lr, &rt, 0)))
	{
		DWORD* p = (DWORD*)lr.pBits;
		for (int i = 0; i < FLOOR_WIDTH * FLOOR_HEIGHT; i++)
		{
			if (map[i] == MAP_STATE_EMPTY)
			{
				p[i] = maskP[i];
			}
			if (map[i] == MAP_STATE_EDGE)
			{
				p[i] = D3DCOLOR_ARGB(255, 0, 0, 0);
			}
			if (map[i] == MAP_STATE_VISITED)
			{
				p[i] = floorP[i];
			}
			if (map[i] == MAP_STATE_VISITING)
			{
				p[i] = D3DCOLOR_ARGB(255, 255, 0, 0);
			}
		}


		(*floorTex)->UnlockRect(0);
	}


}



void FirstGamePage::Update()
{
	gameSystem.Update();
	MapUpdate();
}

void FirstGamePage::Render()
{

	D3DXVECTOR3 cen;
	D3DXVECTOR3 pos;

	spr->Begin(D3DXSPRITE_ALPHABLEND);

	pos = { GAME_PAGE_X, GAME_PAGE_Y, 0 };

	spr->Draw(*backgroundTex, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	spr->Draw(*floorTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));




	spr->End();

	gameSystem.Render();
}