#pragma once
#include "Shader.hpp"
#include "Mesh.hpp"

class Material
{
public:
	Shader* shader;
	void (*RenderCallback)(Shader*);
	void SetRenderCallback(void (*f)(Shader*));

	Material(const GLchar* , const GLchar* );
	~Material();
	void Render(Mesh*);
};

Material::Material(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	RenderCallback = nullptr;
	shader=new Shader(vertexPath,fragmentPath);
}

Material::~Material()
{
	delete shader;
}

void Material::Render(Mesh* m)
{
	shader->Use();
	if (RenderCallback != nullptr)
		RenderCallback(shader);
}

void Material::SetRenderCallback(void (*f)(Shader*))
{
	RenderCallback = f;
}