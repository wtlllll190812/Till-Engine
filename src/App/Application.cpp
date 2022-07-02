#include "Application.h"
#define BIND_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)

Application::Application()
{
	mWindows = std::unique_ptr<TillWindow>(TillWindow::Create());
	mWindows->SetEventCallback(BIND_EVENT_FN(OnEvent));
}

Application::~Application()
{
}

void Application::Init()
{
}

void Application::Run()
{
	while (mRunning)
	{
		mWindows->OnUpdate();
	}
}

void Application::OnEvent(EventBase& e)
{
}
