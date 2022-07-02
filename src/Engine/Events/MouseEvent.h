#include "EventBase.h"

class MouseMovedEvent :public EventBase
{
public:
	MouseMovedEvent(float x, float y)
		:mMouseX(x), mMouseY(y)
	{
	}

	inline float GetX() const { return mMouseX; }
	inline float GetY() const { return mMouseY; }

	std::string ToString() const override
	{
		return "MouseMoved  " + std::to_string(mMouseX) + "  " + std::to_string(mMouseY);
	}
	EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
private:
	float mMouseX;
	float mMouseY;
}; 

class MouseScrolledEvent :public EventBase
{
public:
	MouseScrolledEvent(float xOffset, float yOffset)
		:mXOffset(xOffset), mYOffset(yOffset)
	{
	}

	inline float GetXOffset() const { return mXOffset; }
	inline float GetYOffset() const { return mYOffset; }

	std::string ToString() const override
	{
		return "MouseScrolled  " + std::to_string(mXOffset) + "  " + std::to_string(mYOffset);
	}
	EVENT_CLASS_TYPE(MouseScrolled)
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
private:
	float mXOffset;
	float mYOffset;
};

class MouseButtonEvent : public EventBase
{
public:
	inline int GetMouseButton()const { return mMouseButton; }
	EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput)
protected:
	int mMouseButton;
	MouseButtonEvent(int button) :mMouseButton(button) {}
};

class MouseButtonPressedEvent :public MouseButtonEvent
{
public:
	MouseButtonPressedEvent(int MouseButtoncode)
		:MouseButtonEvent(MouseButtoncode)
	{}
	std::string ToString() const override
	{
		return "MouseButtonPressed  " + std::to_string(mMouseButton);
	}
	EVENT_CLASS_TYPE(MouseButtonPressed)
private:
};

class MouseButtonReleasedEvent :public MouseButtonEvent
{
public:
	MouseButtonReleasedEvent(int MouseButtoncode)
		:MouseButtonEvent(MouseButtoncode)
	{}
	std::string ToString() const override
	{
		return "MouseButtonReleased  " + std::to_string(mMouseButton);
	}

	EVENT_CLASS_TYPE(MouseButtonReleased)
};