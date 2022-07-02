#pragma once
#include "EventBase.h"


/// <summary>
/// 按键事件基类
/// </summary>
class KeyEvent : public EventBase
{
public:
	inline int GetKeyCode()const { return mKeyCode; }
	EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
protected:
	int mKeyCode;
	KeyEvent(int keycode) :mKeyCode(keycode) {}
};

/// <summary>
/// 按键按下事件
/// </summary>
class KeyPressedEvent :public KeyEvent
{
public:
	KeyPressedEvent(int keycode, int repeatCount) 
		:KeyEvent(keycode), mRepeatCount(repeatCount) 
	{}
	inline int GetReapeatCount() const { return mRepeatCount; }
	std::string ToString() const override
	{
		return "KeyPressed  "+std::to_string(mKeyCode);
	}

	EVENT_CLASS_TYPE(KeyPressed)
private:
	int mRepeatCount;
}; 

/// <summary>
/// 按键抬起事件
/// </summary>
class KeyReleasedEvent :public KeyEvent
{
public:
	KeyReleasedEvent(int keycode) 
		:KeyEvent(keycode) 
	{}
	std::string ToString() const override
	{
		return "KeyReleased  " + std::to_string(mKeyCode);
	}

	EVENT_CLASS_TYPE(KeyReleased)
};