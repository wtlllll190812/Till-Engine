#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "TillPch.h"

class GuiWindows;
class Screen : public Singleton<Screen>
{
public:
	GLFWwindow* window;
	int width;
	int heigth;

	Screen(int, int);
	Screen();
	~Screen();

	/// <summary>
	/// 显示窗口
	/// </summary>
	void Display();

	/// <summary>
	/// 窗口是否关闭
	/// </summary>
	/// <returns>是否关闭</returns>
	bool isClosed();

	/// <summary>
	/// imgui初始化
	/// </summary>
	void GuiInit();

	/// <summary>
	/// 渲染Gui
	/// </summary>
	void GuiRender();

	/// <summary>
	/// 注册窗口
	/// </summary>
	void RegisterGuiWindows(std::shared_ptr<GuiWindows>);

	void Init();

private:
	std::vector<std::shared_ptr<GuiWindows>> uiWindows;
};
