#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <vector>


class Mesh
{
public:
	GLuint VAO;
	GLuint VBO;
	//GLuint EBO;

	Mesh(int, std::vector<int>, GLfloat[], int);
	Mesh();
	~Mesh();
private:
	void Init(int , std::vector<int> , GLfloat[], int );
};


