#include "GameLoop.h"
#include <ctime>
#include "Time.h"
#include <iostream>
#include "Screen.h"
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
	if (Awake != nullptr)Awake();
	while (!Screen::instance().isClosed())
	{
		Time::unscaledDeltaTime = (double)clock() / CLOCKS_PER_SEC - Time::unscaledTime;
		Time::deltaTime = Time::unscaledDeltaTime * Time::timeScale;
		Time::unscaledTime += Time::unscaledDeltaTime;
		Time::time += Time::deltaTime;

		if (Update != nullptr)Update();
		if (Time::time - Time::fixedTime >= 1 / (double)frame)
		{
			if (FixedUpdate != nullptr)FixedUpdate();
			Time::fixedTime = Time::time;
		}
		if (LateUpdate != nullptr)LateUpdate();
		//std::cout << GetFPS() << std::endl;
		Time::frameCount++;
	}
}

float GameLoop::GetFPS()
{
	return Time::frameCount/ Time::unscaledTime;
}
