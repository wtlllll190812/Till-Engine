#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include<iostream>
#include"Singleton .h"


class Screen :public Singleton<Screen>
{
public:
	GLFWwindow* window;
	int width;
	int heigth;

	Screen(int, int);
	Screen();
	/// <summary>
	/// 显示窗口
	/// </summary>
	void Display();

	/// <summary>
	/// 窗口是否关闭
	/// </summary>
	/// <returns>是否关闭</returns>
	bool isClosed();

private:
	void Init();
};
