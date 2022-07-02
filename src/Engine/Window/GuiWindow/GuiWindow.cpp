#include "GuiWindow.h"

GuiWindow::GuiWindow(void (*f)(), const char *_name)
{
	RenderCallBack = f;
	name = _name;
}

GuiWindow::GuiWindow(const char *_name)
{
	RenderCallBack = []()
	{ ImGui::ShowDemoWindow(); };
	name = _name;
}

void GuiWindow::Render()
{
	if (RenderCallBack != nullptr)
		RenderCallBack();
}