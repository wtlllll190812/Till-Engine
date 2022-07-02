#include"Material.h"
#include"GameObject.h"

Material::Material(const GLchar* vertexPath, const GLchar* fragmentPath)
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