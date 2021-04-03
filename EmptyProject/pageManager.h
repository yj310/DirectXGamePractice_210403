#pragma once
#include "page.h"

class PageManager
{
public:
	
	PageManager();

	Page* currentPage;
	
	

	

	void createMainPage();
	void createFirstGamePage();

	void Update();
	void Render();


};