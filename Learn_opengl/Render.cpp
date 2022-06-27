#include"Material.h"

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