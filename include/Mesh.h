#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <vector>

class Mesh
{
public:
	GLuint VAO; //顶点数组对象
	GLuint VBO; //顶点缓冲对象
	//GLuint EBO;

	Mesh(int, std::vector<int>, GLfloat[], int);
	Mesh();
	~Mesh();
private:
	void Init(int, std::vector<int>, GLfloat[], int);
};
