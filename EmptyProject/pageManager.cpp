#include "DXUT.h"
#include "global.h"
#include "pageManager.h"
#include "MainPage.h"
#include "firstGamePage.h"

PageManager::PageManager()
{
	currentPage = nullptr;
}

void PageManager::createMainPage()
{
	if (currentPage != nullptr)
	{
		delete currentPage;
	}
	currentPage = new MainPage();
}

void PageManager::createFirstGamePage()
{
	if (currentPage != nullptr)
	{
		delete currentPage;
	}
	currentPage = new FirstGamePage();
}

void PageManager::Update()
{
	currentPage->Update();
}

void PageManager::Render()
{
	currentPage->Render();
}

void PageManager::deleteCurrent()
{
	if (currentPage != nullptr)
	{
		delete currentPage;
	}
}