#include "DXUT.h"
#include "gameSystem.h"


GameSystem::GameSystem()
{
	player = new Player();
}





void GameSystem::Update()
{
	player->Update();
}

void GameSystem::Render()
{
	player->Render();

}

void GameSystem::DeleteTextures()
{
	delete player;
}