#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class GuiWindow
{
public:
	GuiWindow(void (*f)(), const char *);
	GuiWindow(const char *);
	void Render();

private:
	const char *name;
	void (*RenderCallBack)();
};
