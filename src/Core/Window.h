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

enum class CullMode
{
	front,
	back,
	both
};
enum class DepthTestFunc
{
	always,
	never,
	less,
	greater,
	equal,
	lEqual,
	gEqual,
	notEqual,
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
	
	/// <summary>
	/// 窗口渲染函数
	/// </summary>
	virtual void DrawFunc() = 0;
	
	/// <summary>
	/// 每帧渲染结束时调用
	/// </summary>
	virtual void OnRenderEnd() = 0;
	
	/// <summary>
	/// 获取窗口宽度
	/// </summary>
	virtual unsigned int GetWidth() const = 0;
	
	/// <summary>
	/// 获取窗口高度
	/// </summary>
	virtual unsigned int GetHeight() const = 0;
	
	/// <summary>
	/// 获取当前平台的窗口对象
	/// </summary>
	virtual void* GetWindow() const
	{
		return nullptr;
	}

	/// <summary>
	/// 获取指定FBO
	/// </summary>
	/// <param name="index">FBO编号</param>
	virtual FrameBuffer* GetFrameBuffer(int index = 0) = 0;
	
	/// <summary>
	/// 设定当前FBO上下文
	/// </summary>
	/// <param name="index"></param>
	virtual void SetFrameBuffer(int index = 0) = 0;
	virtual void SetFrameBuffer(FrameBuffer*) = 0;
	
	/// <summary>
	/// 获取主FBO
	/// </summary>
	virtual FrameBuffer* GetMianFrameBuffer(int index = 0) = 0;
	
	/// <summary>
	/// 添加FBO
	/// </summary>
	virtual FrameBuffer* AddFrameBuffer(BufferType type) = 0;

	virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
	
	/// <summary>
	/// 设定垂直同步
	/// </summary>
	virtual void SetVSync(bool enabled) = 0;
	
	virtual bool IsVSync() const = 0;

	virtual void SetDepthTest(bool isOn)=0;

	virtual void SetDepthFunc(DepthTestFunc func) = 0;

	virtual void SetDepthWrite(bool isOn) = 0;

	virtual void SetCullFace(CullMode mode) = 0;

	virtual void SetSRGB(bool isOn) = 0;

	virtual float GetTime() = 0;

	//窗口工厂函数
	static Window* Create(const WindowProps& props = WindowProps());
};