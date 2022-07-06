#pragma once
#include "Window.h"
#include "Singleton.h"
#include "TLCore.h"
#include "ApplicationEvent.h"
#include <memory>

class ImguiLayer;
class Layer;
class GameObject;
class Scene;
class GameLoop;
class EditorLayer;
class LayerStack;
class Application :public Singleton<Application>
{
public:
	bool mRunning = true;
	std::unique_ptr<Window> mWindows;
public:
	Application();
	~Application();

	inline void PushLayer(Layer* layer);
	inline void PushOverlay(Layer* layer) ;
	inline EditorLayer* GetEditorLayer() { return editorLayer; }
	void Init();
	void Run();
	void OnEvent(EventBase& e);
private:
	EditorLayer* editorLayer;
	std::shared_ptr<LayerStack> mLayerStack;
	std::shared_ptr<GameLoop> mainLoop;
	std::shared_ptr<Scene> currentScene;
	std::shared_ptr<GameObject> currentObj;

private:
	bool OnWindowsClose(WindowCloseEvent& e);
};
