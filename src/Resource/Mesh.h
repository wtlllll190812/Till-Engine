#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <string>

struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
};

class Mesh
{
public:
	unsigned int VAO; 
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	Mesh();
	~Mesh();
	void Draw();
	unsigned int GetSize() { return static_cast<unsigned int>(indices.size()); }
private:
	unsigned int VBO; //顶点缓冲对象
	unsigned int EBO; 
private:
	void Init();
};
