#pragma once
#include "EventBase.h"

/// <summary>
/// 窗口关闭事件
/// </summary>
class WindowCloseEvent : public EventBase
{
public:
	WindowCloseEvent() {}
	EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

/// <summary>
/// 窗口调整事件
/// </summary>
class WindowResizeEvent : public EventBase
{
public:
	WindowResizeEvent(unsigned int width, unsigned int heigth)
		:mWidth(width), mHeight(heigth)
	{}

	inline unsigned int GetWidth() const { return mWidth; }
	inline unsigned int GetHeight() const { return mHeight; }

	std::string ToString() const override
	{
		return "WindowReSize  " + std::to_string(mWidth) + "  " + std::to_string(mHeight);
	}

	EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
private:
	unsigned int mWidth;
	unsigned int mHeight;
};
