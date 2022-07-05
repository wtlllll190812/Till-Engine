#pragma once
#include"TillPch.h"
#include "EventBase.h"

/// <summary>
/// 窗口属性
/// </summary>
struct WindowProps
{
	std::string Title;
	unsigned int Width;
	unsigned int Height;

	WindowProps(const std::string& title = "Till Engine",
		unsigned int width = 1080,
		unsigned int height = 720)
		:Title(title), Width(width), Height(height)
	{
	}
};

/// <summary>
/// 窗口基类
/// </summary>
class Window
{
public:
	using EventCallbackFn = std::function<void(EventBase&)>;

	virtual ~Window() {};
	virtual void OnRender() = 0;
	virtual void OnRenderEnd() = 0;

	virtual unsigned int GetWidth() const = 0;
	virtual unsigned int GetHeight() const = 0;
	virtual void* GetWindow() const 
	{
		Debug::GetEngineLogger()->warn("sdsd");
		return nullptr;
	}
	virtual void* GetFrameBuffer(int index=0) = 0;
	virtual void SetFrameBuffer(int index=0)=0;
	virtual void AddFrameBuffer()=0;

	virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
	virtual void SetVSync(bool enabled) = 0;
	virtual bool IsVSync() const = 0;

	static Window* Create(const WindowProps& props = WindowProps());
};