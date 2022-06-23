#include "GameLoop.h"
#include <ctime>
using namespace std;

GameLoop::GameLoop(int _frame)
{
	endLoop = false;
	frame = _frame;
	Awake = nullptr;
	Update = nullptr;
	LateUpdate = nullptr;
	FixedUpdate = nullptr;
}

GameLoop::~GameLoop()
{
}

void GameLoop::SetAwakeCallback(void(*f)())
{
	Awake = f;
}

void GameLoop::SetUpdateCallback(void(*f)())
{
	Update = f;
}

void GameLoop::SetFixedUpdateCallback(void(*f)())
{
	FixedUpdate = f;
}

void GameLoop::SetLateUpdateCallback(void(*f)())
{
	LateUpdate = f;
}

void GameLoop::StartLoop()
{
	clock_t start = clock();
	while (true)
	{
		if(Update!=nullptr)Update();
		if ((double)(clock() - start) / CLOCKS_PER_SEC >= 1 / (double)frame)
		{
			if (FixedUpdate != nullptr)FixedUpdate();
			start = clock();
		}
		if (LateUpdate != nullptr)LateUpdate();
	}
}
