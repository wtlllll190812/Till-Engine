#pragma once
#ifndef SHADER_H
#define SHADER_H
#include <GL/glew.h>; // 包含glew来获取所有的必须OpenGL头文件

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


using namespace std;

class Shader
{
public:
	// 程序ID
	GLuint Program;
	// 构造器读取并构建着色器
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	// 使用程序
	void Use();
};

#endif
