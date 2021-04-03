#pragma once
#include "page.h"

class PageManager
{
public:
	
	PageManager();

	Page* currentPage;
	
	

	

	void createMainPage();
	void createFirstGamePage();
	void deleteCurrent();

	void Update();
	void Render();


};