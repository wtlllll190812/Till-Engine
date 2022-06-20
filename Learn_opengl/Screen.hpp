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

Screen::Screen(const GLuint w, const GLuint h) :width(w), heigth(h)
{
    glfwInit();//初始化GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//配置opengl版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//配置opengl版本
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//使用核心模式,使用旧版函数时会出错
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);//禁止调整窗口大小

    window = glfwCreateWindow(width, heigth, "LearnOpenGL", nullptr, nullptr);//创建窗口并设置窗口大小

    //创建失败时
    if (window == nullptr)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);//设定为当前窗口
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //初始化GLEW,用于管理opengl的函数指针
    glewExperimental = GL_TRUE;
    //初始化失败时
    if (glewInit() != GLEW_OK)
    {
        cout << "Failed to initialize GLEW" << endl;
        return;
    }

    //设置窗口
    glViewport(0, 0, width, heigth);//前两个参数控制左下角的位置
    //启用深度测试
    glEnable(GL_DEPTH_TEST);
}

void Screen::Display()
{
    glfwPollEvents();

    //清空屏幕以及缓存区
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Screen::isClosed()
{
    return !glfwWindowShouldClose(window);
}