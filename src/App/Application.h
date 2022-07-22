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
	EditorLayer* editorLayer;
public:
	Application();
	~Application();

	//添加层级
	inline void PushLayer(Layer* layer);
	inline void PushOverlay(Layer* layer);
	//获取编辑器层级
	inline const EditorLayer* GetEditorLayer() { return editorLayer; }
	//初始化应用
	void Init();
	//运行应用
	void Run();
	//处理事件
	void OnEvent(EventBase& e);

private:
	//层级栈
	std::shared_ptr<LayerStack> mLayerStack;
	//游戏主循环
	std::shared_ptr<GameLoop> mainLoop;
	//当前场景
	std::shared_ptr<Scene> currentScene;

private:
	bool OnWindowsClose(WindowCloseEvent& e);
};
