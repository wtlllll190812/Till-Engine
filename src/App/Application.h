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
/// <summary>
/// 引擎主程序
/// </summary>
class Application :public Singleton<Application>
{
public:
	bool mRunning = true;
	std::unique_ptr<Window> mWindows;
	EditorLayer* mEditorLayer;
public:
	Application();
	~Application();

	/// <summary>
	/// 添加新层级
	/// </summary>
	inline void PushLayer(Layer* layer);
	inline void PushOverlay(Layer* layer);
	
	/// <summary>
	/// 获取编辑器层级
	/// </summary>
	inline const EditorLayer* GetEditorLayer() { return mEditorLayer; }
	
	/// <summary>
	/// 初始化应用
	/// </summary>
	void AppInit();
	
	/// <summary>
	/// 运行应用
	/// </summary>
	void AppRun();
	
	/// <summary>
	/// 处理事件
	/// </summary>
	void OnEvent(EventBase& e);

private:
	/// <summary>
	/// 层级栈
	/// </summary>
	std::shared_ptr<LayerStack> mLayerStack;
	
	/// <summary>
	/// 游戏主循环
	/// </summary>
	std::shared_ptr<GameLoop> mainLoop;
	
	/// <summary>
	/// 当前场景
	/// </summary>
	std::shared_ptr<Scene> mCurrentScene;

private:
	/// <summary>
	/// 窗口关闭时
	/// </summary>
	bool OnWindowsClose(WindowCloseEvent& e);
};
