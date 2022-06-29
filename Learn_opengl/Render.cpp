#include"Material.h"

Material::Material(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	RenderCallback = nullptr;
	shader = new Shader(vertexPath, fragmentPath);
}

Material::Material()
{
	RenderCallback = nullptr;
	shader = new Shader("vert.shader", "frag.shader");
}

Material::~Material()
{
	delete shader;
}

void Material::Render(shared_ptr<Mesh> m)
{
	glBindVertexArray(m->VAO);
	if (RenderCallback != nullptr)
		RenderCallback(shader, this);
	glBindVertexArray(0);
}

void Material::SetRenderCallback(void (*f)(Shader*, Material*))
{
	RenderCallback = f;
}