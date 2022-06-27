#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include<iostream>

class Screen
{
public:
	GLFWwindow* window;
	const GLuint width;
	const GLuint heigth;

	Screen(GLuint, GLuint);
	/// <summary>
	/// 显示窗口
	/// </summary>
	void Display();

	/// <summary>
	/// 窗口是否关闭
	/// </summary>
	/// <returns>是否关闭</returns>
	bool isClosed();
};

