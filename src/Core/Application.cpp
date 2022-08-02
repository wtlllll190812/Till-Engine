#include "Application.h"
#include "AssetImporter.h"
#include "GameLoop.h"
#include "Scene.h"
#include "Debug.h"
#include "LayerStack.h"
#include "EditorLayer.h"
#include "RenderSystem.h"
#include "Input.h"
#include "TLTime.h"

#include <string>
#include <cmath>

using namespace std;

Application::Application()
{
	Debug::Init();
	mWindows = unique_ptr<Window>(Window::Create());
	mainLoop = shared_ptr<GameLoop>(new GameLoop(10));
	mLayerStack = shared_ptr<LayerStack>(new LayerStack());
}

Application::~Application()
{
}

inline void Application::PushLayer(Layer *layer)
{
	mLayerStack->PushLayer(layer);
}

inline void Application::PushOverlay(Layer *layer)
{
	mLayerStack->PushOverlay(layer);
}

void Application::AppInit()
{
	Debug::GetEngineLogger()->info("Engine start init");
	AssetImporter::Init();
	Input::Init(mWindows);

	mWindows->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	mCurrentScene = shared_ptr<Scene>(new Scene(DATA_PATH "test.xml"));
	mEditorLayer = new EditorLayer(mCurrentScene);
	PushOverlay(mEditorLayer);

	RenderSystem::instance().SetCamera(mEditorLayer->GetEditorCamera());
	Debug::GetEngineLogger()->info("Engine inited");
}

void Application::AppRun()
{
	AppInit();
	mainLoop->SetUpdateCallback([this]()
		{
			Input::Update();
			mWindows->DrawFunc();
				
			for (auto layer : *mLayerStack)
			{
				layer->OnUpdate();
			}
			mWindows->OnRenderEnd(); 
		});
	Debug::GetAppLogger()->info("start loop");
	mainLoop->StartLoop();
}

void Application::OnEvent(EventBase &e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowsClose));

	for (auto it = (*mLayerStack).end(); it != (*mLayerStack).begin();)
	{
		(*--it)->OnEvent(e);
		if (e.mHandled)
			break;
	}
}

bool Application::OnWindowsClose(WindowCloseEvent &e)
{
	mRunning = false;
	return true;
}