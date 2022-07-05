#include"Material.h"
#include"GameObject.h"
#include "Shader.h"
#include <GL/glew.h> // 包含glew来获取所有的必须OpenGL头文件

Material::Material(const char* vertexPath, const char* fragmentPath)
{
	RenderCallback = nullptr;
	shader = new Shader(vertexPath, fragmentPath);
}

Material::Material()
{
	RenderCallback = nullptr;
	shader = new Shader("../shaders/vert.shader", "../shaders/frag.shader");
}

Material::~Material()
{
	delete shader;
}

void Material::Render(GameObject* object, shared_ptr<Mesh> m)
{
	glBindVertexArray(m->VAO);
	shader->Use();
	if (RenderCallback != nullptr)
		RenderCallback(object, shader, this);
	glBindVertexArray(0);
}

void Material::SetRenderCallback(void (*f)(GameObject*, Shader*, Material*))
{
	RenderCallback = f;
}