#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
#include<iostream>

#include <SOIL2/SOIL2.h>
#include <string>
class Texture
{
public:
	GLuint texture;
	int width, height;
	Texture(std::string);
	~Texture();

private:
};

