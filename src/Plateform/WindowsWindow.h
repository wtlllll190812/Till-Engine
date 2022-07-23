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

	void DrawFunc() override;
	void OnRenderEnd() override;

	inline unsigned int GetWidth() const override { return mData.Width; }
	inline unsigned int GetHeight() const override { return mData.Height; }

	inline virtual void SetEventCallback(const EventCallbackFn& callback) override { mData.EventCallback = callback; }

	inline void* GetWindow()const{return mWindow;}
	inline FrameBuffer* GetFrameBuffer(int index = 0)override { return framebuffer[index]; }
	inline FrameBuffer* AddFrameBuffer(BufferType type) override { FrameBuffer* buffer = new FrameBuffer(type); framebuffer.push_back(buffer); return buffer; }
	inline FrameBuffer* GetMianFrameBuffer(int index = 0) override { return mainBuffer; }

	void SetFrameBuffer(int index = 0)override;
	void SetFrameBuffer(FrameBuffer*)override;
	void SetVSync(bool enabled) override;
	bool IsVSync() const override;
private:
	virtual void Init(const WindowProps& props);
	virtual void ShutDown();
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