#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <vector>

#include "Texture.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};
class Mesh
{
public:
	unsigned int VAO; //顶点数组对象
	unsigned int VBO; //顶点缓冲对象
	unsigned int EBO; //顶点缓冲对象

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	// GLuint EBO;

	Mesh(int, std::vector<int>, float[], int);
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	Mesh();
	~Mesh();

private:
	void Init(int, std::vector<int>, float[], int);
};
