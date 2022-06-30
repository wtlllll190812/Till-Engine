#include "GuiWindows.h"

GuiWindows::GuiWindows(void(*f)(),const char* _name)
{
    RenderCallBack = f;
    name = _name;
}

GuiWindows::GuiWindows(const char* _name)
{
    RenderCallBack = []() {ImGui::ShowDemoWindow(); };
    name = _name;
}

void GuiWindows::Render()
{
    if(RenderCallBack!=nullptr)RenderCallBack();
}


