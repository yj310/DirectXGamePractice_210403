#include "DXUT.h"
#include "global.h"
#include "firstGamePage.h"


FirstGamePage::FirstGamePage()
{

	backgroundTexture = new LPDIRECT3DTEXTURE9();
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
		, backgroundTexture);

	floorTexture = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/floor.png"
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
		, floorTexture);



	D3DXCreateSprite(DXUTGetD3D9Device(), &spr);


}

void FirstGamePage::Update()
{

}

void FirstGamePage::Render()
{

	D3DXVECTOR3 cen = { FLOOR_WIDTH / 2, FLOOR_HEIGHT / 2, 0 };
	D3DXVECTOR3 pos = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0 };

	spr->Begin(D3DXSPRITE_ALPHABLEND);
	spr->Draw(*backgroundTexture, nullptr, nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	spr->Draw(*floorTexture, nullptr, &cen, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
	spr->End();
}