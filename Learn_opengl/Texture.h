#pragma once
#include<iostream>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

class Texture
{
public:
	GLuint texture;
	int width, height;
	Texture(std::string);
	~Texture();

private:

};

