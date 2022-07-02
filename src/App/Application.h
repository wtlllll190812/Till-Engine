#pragma once
#include "TillPch.h"
#include "EventBase.h"
#include "WindowsWindow.h"

class Application
{
public:
	Application();
	~Application();
	void Init();
	void Run();
	void OnEvent(EventBase& e);
private:
	std::unique_ptr<TillWindow> mWindows;
	bool mRunning = true;
};

