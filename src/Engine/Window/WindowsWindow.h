#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include "TillWindow.h"


class WindowsWindow :public TillWindow
{
public:
	WindowsWindow(const WindowProps& props);
	virtual ~WindowsWindow();

	void OnUpdate() override;
	
	inline unsigned int GetWidth() const override { return mData.Width; }
	inline unsigned int GetHeight() const override { return mData.Height; }

	inline virtual void SetEventCallback(const EventCallbackFn& callback) override { mData.EventCallback = callback; }

	void SetVSync(bool enabled) override;
	bool IsVSync() const override;
private:
	virtual void Init(const WindowProps& props);
	virtual void ShutDown();
private:
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