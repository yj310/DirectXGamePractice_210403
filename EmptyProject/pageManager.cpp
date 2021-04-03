#include "DXUT.h"
#include "global.h"
#include "pageManager.h"
#include "MainPage.h"
#include "firstGamePage.h"

PageManager::PageManager()
{
	
}

void PageManager::createMainPage()
{
	if (currentPage != nullptr)
	{
		delete currentPage;
	}
	currentPage = new MainPage;
}

void PageManager::createFirstGamePage()
{
	if (currentPage != nullptr)
	{
		delete currentPage;
	}
	currentPage = new FirstGamePage;
}

void PageManager::Update()
{
	currentPage->Update();
}

void PageManager::Render()
{
	currentPage->Render();
}