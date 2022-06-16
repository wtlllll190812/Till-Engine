#pragma once
#include<iostream>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
using namespace std;

class Screen
{
public:
	GLFWwindow* window;
	const GLuint width;
	const GLuint heigth;

	Screen(GLuint,  GLuint);
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
