#pragma once
using namespace std;

class Shader
{
public:
	// 程序ID
	unsigned int Program;
	// 构造器读取并构建着色器
	Shader(const char* vertexPath, const char* fragmentPath);
	// 使用程序
	void Use();
};