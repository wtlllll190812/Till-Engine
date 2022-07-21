#pragma once
#include "TLCore.h"
#include <string>

/// <summary>
/// 事件类型
/// </summary>
enum class EventType
{
	None = 0,
	WindowClose,
	WindowResize,
	WindowFocus,
	WindowLostFocus,
	WindowMoves,
	AppTick,
	AppUpdate,
	AppRender,
	KeyPressed,
	KeyReleased,
	MouseButtonPressed,
	MouseButtonReleased,
	MouseMoved,
	MouseScrolled
};

/// <summary>
/// 事件分类
/// </summary>
enum EventCategory
{
	None = 0,
	EventCategoryApplication = BIT(0),
	EventCategoryInput = BIT(1),
	EventCategoryKeyboard = BIT(2),
	EventCategoryMouse = BIT(3),
	EventCategoryMouseButton = BIT(4)
};

#define EVENT_CLASS_TYPE(type)                                                  \
	static EventType GetStaticType() { return EventType::##type; }              \
	virtual EventType GetEventType() const override { return GetStaticType(); } \
	virtual const char *GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
	virtual int GetCategoryFlags() const override { return category; }

/// <summary>
/// 事件类基类
/// </summary>
class EventBase
{
public:

	virtual const char* GetName() const = 0;

	virtual EventType GetEventType() const = 0;

	virtual int GetCategoryFlags() const = 0;

	virtual std::string ToString() const { return GetName(); };

	/// <summary>
	/// 是否属于该类型
	/// </summary>
	inline bool IsInCategory(EventCategory category)
	{
		return GetCategoryFlags() & category;
	}

	bool mHandled = false;
};

/// <summary>
/// 事件调度类
/// </summary>
class EventDispatcher
{
	template <typename T>
	using EventFn = std::function<bool(T&)>;

public:
	EventDispatcher(EventBase& event) : mEvent(event) {}
	template <typename T>

	/// <summary>
	/// 判断事件类型是否符合
	/// </summary>
	bool Dispatch(EventFn<T> func)
	{
		if (mEvent.GetEventType() == T::GetStaticType())
		{
			mEvent.mHandled = func(*(T*)&mEvent);
			return true;
		}
		return false;
	}

private:
	EventBase& mEvent;
};