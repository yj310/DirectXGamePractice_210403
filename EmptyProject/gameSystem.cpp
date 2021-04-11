#include "DXUT.h"
#include "gameSystem.h"
#include "global.h"
#include <stack>

using namespace std;

GameSystem::GameSystem()
{
	player = new Player();
	isSpace = false;
	myLand = 0;
	isFinish = false;


	clearTex = new LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, "resource/image/clear.png"
		, D3DX_DEFAULT_NONPOW2
		, D3DX_DEFAULT_NONPOW2
		, 0, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 0, nullptr, nullptr
		, clearTex);

	D3DXCreateSprite(DXUTGetD3D9Device(), &spr);
}

void GameSystem::GetLand()
{
	myLand = 0;
	for (int i = 0; i < FLOOR_WIDTH * FLOOR_HEIGHT; i++)
	{
		if (map[i] == MAP_STATE_EMPTY)
			virtualMap[i] = MAP_STATE_VIRTUAL_EMPTY;
		else if (map[i] == MAP_STATE_VISITED)
		{
			virtualMap[i] = MAP_STATE_VISITED;
			myLand++;
		}
		else if (map[i] == MAP_STATE_VISITING)
			virtualMap[i] = MAP_STATE_EDGE;
		else if (map[i] == MAP_STATE_EDGE)
			virtualMap[i] = MAP_STATE_EDGE;
	}

	FloodFill();


	for (int i = 0; i < FLOOR_WIDTH * FLOOR_HEIGHT; i++)
	{
		if (virtualMap[i] == MAP_STATE_VIRTUAL_EMPTY)
		{
			map[i] = MAP_STATE_VISITED;
			myLand++;
		}
		else
			map[i] = virtualMap[i];
	}

	EdgeUpdate();
}

void GameSystem::FloodFill()
{
	stack<Point> points;
	points.push(Point(500, 500));

	while (!points.empty())
	{
		const Point p = points.top();
		points.pop();

		if (p.x < 0
			|| p.x >= FLOOR_WIDTH
			|| p.y < 0
			|| p.y >= FLOOR_HEIGHT)
			continue;

		if (virtualMap[p.y * FLOOR_WIDTH + p.x] == MAP_STATE_VIRTUAL_EMPTY)
			virtualMap[p.y * FLOOR_WIDTH + p.x] = MAP_STATE_EMPTY;
		else
			continue;

		points.push(Point(p.x + 1, p.y));
		points.push(Point(p.x - 1, p.y));
		points.push(Point(p.x, p.y + 1));
		points.push(Point(p.x, p.y - 1));
	}

}

void GameSystem::EdgeUpdate()
{
	for (int y = 0; y < FLOOR_HEIGHT; y++)
	{
		for (int x = 0; x < FLOOR_WIDTH; x++)
		{
			if (map[y * FLOOR_WIDTH + x] == MAP_STATE_EDGE)
			{

				int left_top = map[(y - 1) * FLOOR_WIDTH + (x - 1)];
				int top = map[(y - 1) * FLOOR_WIDTH + (x)];
				int right_top = map[(y - 1) * FLOOR_WIDTH + (x + 1)];

				int left = map[(y)*FLOOR_WIDTH + (x - 1)];
				int right = map[(y)*FLOOR_WIDTH + (x + 1)];

				int left_bottom = map[(y + 1) * FLOOR_WIDTH + (x - 1)];
				int bottom = map[(y + 1) * FLOOR_WIDTH + (x)];
				int right_bottom = map[(y + 1) * FLOOR_WIDTH + (x + 1)];

				if (y - 1 > 0)
				{
					if ((x - 1) >= 0
						&& left_top == MAP_STATE_EMPTY)
					{
						continue;
					}

					if (top == MAP_STATE_EMPTY)
					{
						continue;
					}

					if ((x + 1) < FLOOR_WIDTH
						&& right_top == MAP_STATE_EMPTY)
					{
						continue;
					}
				}


				if ((x - 1) >= 0
					&& left == MAP_STATE_EMPTY)
				{
					continue;
				}

				if ((x + 1) < FLOOR_WIDTH
					&& right == MAP_STATE_EMPTY)
				{
					continue;
				}


				if (y + 1 < FLOOR_HEIGHT)
				{
					if ((x - 1) >= 0
						&& left_bottom == MAP_STATE_EMPTY)
					{
						continue;
					}

					if (bottom == MAP_STATE_EMPTY)
					{
						continue;
					}

					if ((x + 1) < FLOOR_WIDTH
						&& right_bottom == MAP_STATE_EMPTY)
					{
						continue;
					}
				}


				map[y * FLOOR_WIDTH + x] = MAP_STATE_VISITED;
				myLand++;


			}
		}
	}
}


void GameSystem::Update()
{
	if (!isFinish)
	{
		int posX = player->getPos().x;
		int posY = player->getPos().y;
		isSpace = false;
		if ((GetAsyncKeyState(VK_SPACE) & 0x8000) != 0)
			isSpace = true;

		if ((GetAsyncKeyState(VK_LEFT) & 0x8000) != 0)
		{

			if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_EDGE
				&& map[posY * FLOOR_WIDTH + (posX - 1)] == MAP_STATE_EDGE)
			{
				if (posX - 1 >= 0)
					player->move({ -1, 0 });
			}

			else if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_EDGE
				&& map[posY * FLOOR_WIDTH + (posX - 1)] == MAP_STATE_EMPTY
				&& isSpace)
			{
				startX = posX;
				startY = posY;
				player->move({ -1, 0 });
				map[(posY)*FLOOR_WIDTH + (posX - 1)] = MAP_STATE_VISITING;
			}

			else if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_VISITING
				&& map[posY * FLOOR_WIDTH + (posX - 1)] == MAP_STATE_EMPTY)
			{
				player->move({ -1, 0 });
				map[(posY)*FLOOR_WIDTH + (posX - 1)] = MAP_STATE_VISITING;
			}

			else if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_VISITING
				&& map[posY * FLOOR_WIDTH + (posX - 1)] == MAP_STATE_EDGE)
			{
				player->move({ -1, 0 });
				GetLand();
			}

		}
		else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0)
		{
			if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_EDGE
				&& map[posY * FLOOR_WIDTH + (posX + 1)] == MAP_STATE_EDGE)
			{
				if (posX + 1 < FLOOR_WIDTH)
					player->move({ 1, 0 });
			}

			else if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_EDGE
				&& map[posY * FLOOR_WIDTH + (posX + 1)] == MAP_STATE_EMPTY
				&& isSpace)
			{
				startX = posX;
				startY = posY;
				player->move({ 1, 0 });
				map[(posY)*FLOOR_WIDTH + (posX + 1)] = MAP_STATE_VISITING;
			}

			else if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_VISITING
				&& map[posY * FLOOR_WIDTH + (posX + 1)] == MAP_STATE_EMPTY)
			{
				player->move({ 1, 0 });
				map[(posY)*FLOOR_WIDTH + (posX + 1)] = MAP_STATE_VISITING;
			}

			else if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_VISITING
				&& map[posY * FLOOR_WIDTH + (posX + 1)] == MAP_STATE_EDGE)
			{
				player->move({ 1, 0 });
				GetLand();
			}

		}
		else if ((GetAsyncKeyState(VK_UP) & 0x8000) != 0)
		{
			if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_EDGE
				&& map[(posY - 1) * FLOOR_WIDTH + posX] == MAP_STATE_EDGE)
			{
				if (posY - 1 >= 0)
					player->move({ 0, -1 });
			}

			else if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_EDGE
				&& map[(posY - 1) * FLOOR_WIDTH + posX] == MAP_STATE_EMPTY
				&& isSpace)
			{
				startX = posX;
				startY = posY;
				player->move({ 0, -1 });
				map[(posY - 1) * FLOOR_WIDTH + posX] = MAP_STATE_VISITING;
			}

			else if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_VISITING
				&& map[(posY - 1) * FLOOR_WIDTH + posX] == MAP_STATE_EMPTY)
			{
				player->move({ 0, -1 });
				map[(posY - 1) * FLOOR_WIDTH + posX] = MAP_STATE_VISITING;
			}

			else if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_VISITING
				&& map[(posY - 1) * FLOOR_WIDTH + posX] == MAP_STATE_EDGE)
			{
				player->move({ 0, -1 });
				GetLand();
			}
		}
		else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) != 0)
		{
			if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_EDGE
				&& map[(posY + 1) * FLOOR_WIDTH + posX] == MAP_STATE_EDGE)
			{
				if (posY + 1 < FLOOR_HEIGHT)
					player->move({ 0, 1 });
			}

			else if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_EDGE
				&& map[(posY + 1) * FLOOR_WIDTH + posX] == MAP_STATE_EMPTY
				&& isSpace)
			{
				startX = posX;
				startY = posY;
				player->move({ 0, 1 });
				map[(posY + 1) * FLOOR_WIDTH + posX] = MAP_STATE_VISITING;
			}

			else if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_VISITING
				&& map[(posY + 1) * FLOOR_WIDTH + posX] == MAP_STATE_EMPTY)
			{
				player->move({ 0, 1 });
				map[(posY + 1) * FLOOR_WIDTH + posX] = MAP_STATE_VISITING;
			}

			else if (map[posY * FLOOR_WIDTH + posX] == MAP_STATE_VISITING
				&& map[(posY + 1) * FLOOR_WIDTH + posX] == MAP_STATE_EDGE)
			{
				player->move({ 0, 1 });
				GetLand();
			}
		}

		if (myLand >= ((FLOOR_WIDTH - 2) * (FLOOR_HEIGHT - 2)) / 100.0 * 80.0)
		{
			isFinish = true;
		}


		player->Update();
	}
}

void GameSystem::Render()
{
	player->Render();
	if (isFinish)
	{
		D3DXVECTOR3 pos = { (WINDOW_WIDTH - 600) / 2, (WINDOW_HEIGHT - 200) / 2, 0 };
		spr->Begin(D3DXSPRITE_ALPHABLEND);
		spr->Draw(*clearTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
		spr->End();
	}
}

void GameSystem::DeleteTextures()
{
	delete player;
}