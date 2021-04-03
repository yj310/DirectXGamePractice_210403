#pragma once
#include "page.h"


class FirstGamePage : public Page
{
public:
	FirstGamePage();
	void Update() override;
	void Render() override;


	LPDIRECT3DTEXTURE9* backgroundTexture;
	LPDIRECT3DTEXTURE9* floorTexture;
	LPD3DXSPRITE spr;

};