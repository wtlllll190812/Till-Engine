#pragma once
#include<functional>

class GuiWindow
{
public:
	GuiWindow(const std::function<void()>& f, const char*);
	GuiWindow(const char*);
	void Render();

private:
	const char* name;
	std::function<void()> RenderCallBack;
};
