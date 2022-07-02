#pragma once
#include "EventBase.h"

class KeyEvent : public EventBase
{
public:
	inline int GetKeyCode()const { return mKeyCode; }
	EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
protected:
	int mKeyCode;
	KeyEvent(int keycode) :mKeyCode(keycode) {}
};

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