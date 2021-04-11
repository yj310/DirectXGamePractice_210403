#include "DXUT.h"
#include "player.h"
#include "global.h"


Player::Player()
{
	posX = 0;
	posY = 0;

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