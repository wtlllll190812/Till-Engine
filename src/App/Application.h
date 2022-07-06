#pragma once
#include "Window.h"
#include "LayerStack.h"
#include "Singleton.h"
#include "TLCore.h"
#include "ApplicationEvent.h"
#include <memory>

class ImguiLayer;
class Layer;
class GameObject;
class Scene;
class GameLoop;
class Application :public Singleton<Application>
{
public:
	std::unique_ptr<Window> mWindows;
public:
	Application();
	~Application();

	inline void PushLayer(Layer* layer) { mLayerStack.PushLayer(layer); };
	inline void PushOverlay(Layer* layer) { mLayerStack.PushOverlay(layer); };
	inline ImguiLayer* GetEditorLayer() { return editorLayer; }
	void Init();
	void Run();
	void OnEvent(EventBase& e);
	bool mRunning = true;

private:
	void EditorInit();
	bool OnWindowsClose(WindowCloseEvent& e);

private:
	ImguiLayer* editorLayer;
	LayerStack mLayerStack;
	std::shared_ptr <GameLoop> mainLoop;
	std::shared_ptr<Scene> currentScene;
	std::shared_ptr<GameObject> currentObj;
};
