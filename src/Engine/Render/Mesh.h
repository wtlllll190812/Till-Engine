#pragma once
#include <vector>

class Mesh
{
public:
	unsigned int VAO; //顶点数组对象
	unsigned int VBO; //顶点缓冲对象
	// GLuint EBO;

	Mesh(int, std::vector<int>, float[], int);
	Mesh();
	~Mesh();

private:
	void Init(int, std::vector<int>, float[], int);
};
