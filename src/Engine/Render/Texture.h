#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <iostream>

#include <SOIL2/SOIL2.h>
#include <string>
class Texture
{
public:
	GLuint texture;
	int width, height;
	Texture(std::string);
	Texture();
	~Texture();

private:
	void TextureInit();
};
