#pragma once
#include "EventBase.h"
#include "FrameBuffer.h"

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
class FrameBuffer;
class Window
{
public:
	using EventCallbackFn = std::function<void(EventBase&)>;

	virtual ~Window() {};
	//渲染一帧
	virtual void DrawFunc() = 0;
	//渲染结束时
	virtual void OnRenderEnd() = 0;

	virtual unsigned int GetWidth() const = 0;
	virtual unsigned int GetHeight() const = 0;
	
	//获取当前窗口
	virtual void* GetWindow() const
	{
		return nullptr;
	}

	//获取指定FrameBuffer
	virtual FrameBuffer* GetFrameBuffer(int index = 0) = 0;
	//设定当前帧缓存
	virtual void SetFrameBuffer(int index = 0) = 0;
	virtual void SetFrameBuffer(FrameBuffer*) = 0;
	virtual FrameBuffer* GetMianFrameBuffer(int index = 0) = 0;
	//添加帧缓存
	virtual FrameBuffer* AddFrameBuffer(BufferType type) = 0;

	virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
	//设置垂直同步
	virtual void SetVSync(bool enabled) = 0;
	virtual bool IsVSync() const = 0;

	//窗口工厂函数
	static Window* Create(const WindowProps& props = WindowProps());
};