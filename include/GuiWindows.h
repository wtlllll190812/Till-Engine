#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class GuiWindows
{
public:
    GuiWindows(void(*f)(), const char*);
    GuiWindows(const char*);
    void Render();
private:
    const char* name;
    void (*RenderCallBack)();
};

