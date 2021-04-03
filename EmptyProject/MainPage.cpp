#include "DXUT.h"
#include "global.h"
#include "MainPage.h"


MainPage::MainPage()
{

	texture = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/background.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0
		, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_DEFAULT
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0
		, nullptr
		, nullptr
		, texture);



	D3DXCreateSprite(DXUTGetD3D9Device(), &spr);




}

void MainPage::Update()
{

}

void MainPage::Render()
{
	spr->Begin(D3DXSPRITE_ALPHABLEND);
	spr->Draw(*texture, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	spr->End();

}