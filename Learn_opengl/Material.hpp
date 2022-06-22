#pragma once
#include "Shader.hpp"
#include "Mesh.hpp"
#include "TLEngineCG.hpp"

class Material
{
public:
	Shader* shader;
	int renderQueueIndex = (int)RendererQueue::Geometry;
	void (*RenderCallback)(Shader*, Material*);

	Material(const GLchar*, const GLchar*);
	~Material();

	void SetRenderCallback(void (*f)(Shader*, Material*));
	void Render(Mesh*);
};

Material::Material(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	RenderCallback = nullptr;
	shader = new Shader(vertexPath, fragmentPath);
}

Material::~Material()
{
	delete shader;
}

void Material::Render(Mesh* m)
{
	shader->Use();
	glBindVertexArray(m->VAO);
	if (RenderCallback != nullptr)
		RenderCallback(shader, this);
	glBindVertexArray(0);
}

void Material::SetRenderCallback(void (*f)(Shader*, Material*))
{
	RenderCallback = f;
}