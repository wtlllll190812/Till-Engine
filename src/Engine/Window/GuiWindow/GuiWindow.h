#pragma once

class GuiWindow
{
public:
	GuiWindow(void (*f)(), const char*);
	GuiWindow(const char*);
	void Render();

private:
	const char* name;
	void (*RenderCallBack)();
};
