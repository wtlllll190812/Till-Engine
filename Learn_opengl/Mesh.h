#pragma once
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include <vector>

class Mesh
{
public:
	GLuint VAO;
	GLuint VBO;
	//GLuint EBO;

	Mesh(int, std::vector<int>, GLfloat[], int);
	~Mesh();
private:
};