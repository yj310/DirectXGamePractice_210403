#pragma once
#include "page.h"
#include "gameSystem.h"


class FirstGamePage : public Page
{
public:

	FirstGamePage();
	virtual ~FirstGamePage();
	void Update() override;
	void Render() override;
	void MapUpdate();

	GameSystem gameSystem;


	LPDIRECT3DTEXTURE9* backgroundTex;
	LPDIRECT3DTEXTURE9* floorTex;
	LPDIRECT3DTEXTURE9* maskTex;
	LPD3DXSPRITE spr;




};