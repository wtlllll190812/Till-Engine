#pragma once
#include "Window.h"
#include "LayerStack.h"
#include "Singleton.h"
#include "TLCore.h"
#include "ApplicationEvent.h"
#include <memory>

class ImguiLayer;
class Layer;

class Application :public Singleton<Application>
{
public:
	std::unique_ptr<Window> mWindows;
public:
	Application();
	~Application();

	inline void PushLayer(Layer* layer) { mLayerStack.PushLayer(layer); };
	inline void PushOverlay(Layer* layer) { mLayerStack.PushOverlay(layer); };
	inline ImguiLayer* GetGuiLayer() { return guiLayer; }
	void Init();
	void Run();
	void OnEvent(EventBase& e);
	bool mRunning = true;

private:
	LayerStack mLayerStack;

private:
	bool OnWindowsClose(WindowCloseEvent& e);
	ImguiLayer* guiLayer;
};
