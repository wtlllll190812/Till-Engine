#include "GameLoop.h"
#include "TLTime.h"
#include "Application.h"

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

void GameLoop::SetAwakeCallback(std::function<void()> f)
{
	Awake = f;
}

void GameLoop::SetUpdateCallback(std::function<void()> f)
{
	Update = f;
}

void GameLoop::SetFixedUpdateCallback(std::function<void()> f)
{
	FixedUpdate = f;
}

void GameLoop::SetLateUpdateCallback(std::function<void()> f)
{
	LateUpdate = f;
}

void GameLoop::StartLoop()
{
	if (Awake != nullptr)
		Awake();
	while (Application::instance().mRunning)
	{
		TLTime::unscaledDeltaTime = Application::instance().mWindows->GetTime() - TLTime::unscaledTime;
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