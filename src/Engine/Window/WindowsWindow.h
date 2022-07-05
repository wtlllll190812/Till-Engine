#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include "Window.h"
#include "Application.h"
/// <summary>
/// tillwindow在windows平台下的实现
/// </summary>
class WindowsWindow :public Window
{
public:
	WindowsWindow(const WindowProps& props);
	virtual ~WindowsWindow();

	void OnRender() override;
	void OnRenderEnd() override;

	inline unsigned int GetWidth() const override { return mData.Width; }
	inline unsigned int GetHeight() const override { return mData.Height; }
	inline virtual void SetEventCallback(const EventCallbackFn& callback) override { mData.EventCallback = callback; }
	
	inline virtual void* GetWindow()const
	{
		return mWindow; 
	}
	inline virtual void* GetFrameBuffer(int index = 0)override { return &framebuffer[index]; }
	inline virtual void SetFrameBuffer(int index = 0)override { glBindFramebuffer(GL_FRAMEBUFFER, framebuffer[index]); }
	
	void AddFrameBuffer() override;
	void SetVSync(bool enabled) override;
	bool IsVSync() const override;
private:
	virtual void Init(const WindowProps& props);
	virtual void ShutDown();
	void SetCallback();
private:
	std::vector<GLuint> framebuffer;
	GLFWwindow* mWindow;
	
	struct WindowData
	{
		std::string Title;
		unsigned int Width, Height;
		bool VSync;

		EventCallbackFn EventCallback;
	};
	WindowData mData;

	// 通过 Window 继承

};