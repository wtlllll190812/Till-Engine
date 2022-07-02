#pragma once
#include "TillPch.h"
#include <string>
#include <functional>

class EventBase
{
    virtual std::string GetName() const = 0;
    virtual EventType GetEventType() const = 0;
    virtual int GetCategoryFlags() const = 0;
    virtual std::string Tostring() const { return GetName(); };
    inline bool IsInCategory(EventCategory category)
    {
        return GetCategoryFlags() & category;
    }

private:
    bool mHandled = false;
};

enum class EventType
{
    None = 0,
    WindowsClose,
    WindowsResize,
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
enum EventCategory
{
    None = 0,
    EventCategoryApplication = BIT(0),
    EventCategoryInput = BIT(1),
    EventCategoryKeyboard = BIT(2),
    EventCategoryMouse = BIT(3),
    EventCategoryMouseButton = BIT(4)
};