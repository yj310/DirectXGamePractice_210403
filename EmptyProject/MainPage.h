#pragma once
#include "page.h"


class MainPage : public Page
{
public:
	MainPage();
	void Update() override;
	void Render() override;



	LPDIRECT3DTEXTURE9* texture;
	LPD3DXSPRITE spr;

};