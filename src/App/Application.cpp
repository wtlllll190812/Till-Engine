#include "Application.h"
#include "GameLoop.h"
#include "Scene.h"
#include "Debug.h"
#include "EditorLayer.h"
#include "LayerStack.h"
#include <string>
using namespace std;
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include "Input.h"
#include <cmath>
#include "TLTime.h"
//临时
#include "GameObject.h"
#include "Renderer.h"
#include "Scene.h"
#include "Camera.h"
#include "Light.h"
#include "TLEngineCG.h"
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "UniformBuffer.h"

Application::Application()
{
	Debug::Init();
	mWindows = unique_ptr<Window>(Window::Create());
	mainLoop = shared_ptr<GameLoop>(new GameLoop(10));
	mLayerStack = shared_ptr<LayerStack>(new LayerStack());
	currentScene = shared_ptr<Scene>(new Scene(DATA_PATH "test.xml"));
	editorLayer = new EditorLayer(currentScene);
}

Application::~Application()
{
	delete editorLayer;
}

inline void Application::PushLayer(Layer *layer)
{
	mLayerStack->PushLayer(layer);
}

inline void Application::PushOverlay(Layer *layer)
{
	mLayerStack->PushOverlay(layer);
}

void Application::Init()
{
	mWindows->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	PushOverlay(editorLayer);
	Input::Init();
}

void Application::Run()
{
	Init();
	auto cameraObject = currentScene->Find("camera");
	auto object = currentScene->Find("object");

	mainLoop->SetUpdateCallback([&object, this]()
		{
			Input::Update();
			mWindows->OnRender();
			
			for (auto layer : *mLayerStack)
			{
				layer->OnUpdate();
			}
			/*object->transform->rotation.y = std::cos(TLTime::GetTime());
			object->transform->rotation.x = std::sin(TLTime::GetTime());*/
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