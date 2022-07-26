#pragma once

#include "Window.h"
#include <vector>
#include "FrameBuffer.h"

/// <summary>
/// tillwindow在opengl平台下的实现
/// </summary>
class GLFWwindow;
class WindowsWindow :public Window
{
public:
	WindowsWindow(const WindowProps& props);
	virtual ~WindowsWindow();

	/// <summary>
	/// 窗口渲染函数
	/// </summary>
	void DrawFunc() override;
	
	/// <summary>
	/// 每帧渲染结束时调用
	/// </summary>
	void OnRenderEnd() override;

	/// <summary>
	/// 获取窗口宽度
	/// </summary>
	inline unsigned int GetWidth() const override { return mData.Width; }
	
	/// <summary>
	/// 获取窗口高度
	/// </summary>
	inline unsigned int GetHeight() const override { return mData.Height; }
	inline virtual void SetEventCallback(const EventCallbackFn& callback) override { mData.EventCallback = callback; }

	/// <summary>
	/// 获取当前平台的窗口对象
	/// </summary>
	inline void* GetWindow()const{return mWindow;}
	
	/// <summary>
	/// 获取指定FBO
	/// </summary>
	/// <param name="index">FBO编号</param>
	inline FrameBuffer* GetFrameBuffer(int index = 0)override { return framebuffer[index]; }

	/// <summary>
	/// 添加FBO
	/// </summary>
	inline FrameBuffer* AddFrameBuffer(BufferType type) override { FrameBuffer* buffer = new FrameBuffer(type); framebuffer.push_back(buffer); return buffer; }

	/// <summary>
	/// 获取主FBO
	/// </summary>
	inline FrameBuffer* GetMianFrameBuffer(int index = 0) override { return mainBuffer; }

	/// <summary>
	/// 设定当前FBO上下文
	/// </summary>
	/// <param name="index"></param>
	void SetFrameBuffer(int index = 0)override;
	void SetFrameBuffer(FrameBuffer*)override;

	/// <summary>
	/// 设定垂直同步
	/// </summary>
	void SetVSync(bool enabled) override;
	bool IsVSync() const override;
private:
	/// <summary>
	/// 窗口初始化
	/// </summary>
	virtual void WindowInit(const WindowProps& props);
	
	/// <summary>
	/// 关闭窗口时调用
	/// </summary>
	virtual void ShutDown();

	/// <summary>
	/// 设置窗口回调函数
	/// </summary>
	void SetCallback();
private:
	std::vector<FrameBuffer*> framebuffer;
	FrameBuffer* currentBuffer;
	FrameBuffer* mainBuffer;
	GLFWwindow* mWindow;

	struct WindowData
	{
		std::string Title;
		unsigned int Width, Height;
		bool VSync;

		EventCallbackFn EventCallback;
	};
	WindowData mData;
};