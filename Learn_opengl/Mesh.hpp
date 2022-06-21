#pragma once
#include <GLFW/glfw3.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>


class Mesh
{
public:
    GLuint VAO;
    GLuint VBO;
    //GLuint EBO;

	Mesh(int, std::vector<int>,GLfloat[],int);
	~Mesh();
private:
	
};

Mesh::Mesh(int sum,std::vector<int> settings,GLfloat vertices[],int size)
{
    //顶点缓存
    glGenBuffers(1, &VBO);//设置缓存ID
    //glGenBuffers(1, &EBO);
    //顶点数组对象
    glGenVertexArrays(1, &VAO);//设置缓存ID

    glBindVertexArray(VAO);//绑定顶点数组对象

    glBindBuffer(GL_ARRAY_BUFFER, VBO);//绑定缓存对象
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);//复制数据到缓存
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    int offset=0;
    for (size_t i = 0; i < settings.size(); i++)
    {
        glVertexAttribPointer(i, settings[i], GL_FLOAT, GL_FALSE, sum * sizeof(GLfloat), (GLvoid*)(offset * sizeof(GLfloat)));//设置解析顶点数据的方式
        glEnableVertexAttribArray(i);//启用顶点属性
        offset += settings[i];
    }
    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);
}