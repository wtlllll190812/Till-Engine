#pragma once
#include"TillPch.h"
#include "EventBase.h"

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
class TillWindow
{
public:
	using EventCallbackFn = std::function<void(EventBase&)>;

	virtual ~TillWindow() {};
	virtual void OnUpdate() = 0;
	virtual unsigned int GetWidth() const = 0;
	virtual unsigned int GetHeight() const = 0;

	virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
	virtual void SetVSync(bool enabled) = 0;
	virtual bool IsVSync() const = 0;

	static TillWindow* Create(const WindowProps& props = WindowProps());
};