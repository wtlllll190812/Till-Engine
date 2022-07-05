#include "Application.h"
#include "GameLoop.h"
#include "Scene.h"
#include "TillPch.h"
using namespace std;


Application::Application()
{
	mWindows = std::unique_ptr<Window>(Window::Create());
	mWindows->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	guiLayer = new ImguiLayer();
}

Application::~Application()
{
}

void Application::Init()
{
	PushOverlay(guiLayer);
}

void Application::Run()
{
	mWindows->OnRender();
	for (auto layer : mLayerStack)
	{
		layer->OnUpdate();
	}
	mWindows->OnRenderEnd();
}

void Application::OnEvent(EventBase& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowsClose));
	//Debug::GetEngineLogger()->info(e.ToString());

	for (auto it =mLayerStack.end();it!=mLayerStack.begin();)
	{
		(*--it)->OnEvent(e);
		if (e.mHandled)
			break;
	}
}

bool Application::OnWindowsClose(WindowCloseEvent& e)
{
	mRunning = false;
	return true;
}

