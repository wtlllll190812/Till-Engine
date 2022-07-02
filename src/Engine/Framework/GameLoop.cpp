#include "GameLoop.h"
#include "TLTime.h"
#include "Screen.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

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

void GameLoop::SetAwakeCallback(void (*f)())
{
	Awake = f;
}

void GameLoop::SetUpdateCallback(void (*f)())
{
	Update = f;
}

void GameLoop::SetFixedUpdateCallback(void (*f)())
{
	FixedUpdate = f;
}

void GameLoop::SetLateUpdateCallback(void (*f)())
{
	LateUpdate = f;
}

void GameLoop::StartLoop()
{
	if (Awake != nullptr)
		Awake();
	while (!Screen::instance().isClosed())
	{
		TLTime::unscaledDeltaTime = glfwGetTime() - TLTime::unscaledTime; //(double)clock() / CLOCKS_PER_SEC;
		TLTime::deltaTime = TLTime::unscaledDeltaTime * TLTime::timeScale;
		TLTime::unscaledTime += TLTime::unscaledDeltaTime;
		TLTime::time += TLTime::deltaTime;
		if (Update != nullptr)
			Update();
		if (TLTime::time - TLTime::fixedTime >= 1 / (double)frame)
		{
			if (FixedUpdate != nullptr)
				FixedUpdate();
			TLTime::fixedTime = TLTime::time;
		}
		if (LateUpdate != nullptr)
			LateUpdate();
		// std::cout << GetFPS() << std::endl;
		TLTime::frameCount++;
	}
}

float GameLoop::GetFPS()
{
	return TLTime::frameCount / TLTime::unscaledTime;
}