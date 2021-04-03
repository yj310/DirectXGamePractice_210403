#pragma once
#include "page.h"


class MainPage : public Page
{
public:
	MainPage();
	virtual ~MainPage();
	void Update() override;
	void Render() override;



	LPDIRECT3DTEXTURE9* texture;
	LPD3DXSPRITE spr;

};