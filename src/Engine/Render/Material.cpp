#include"Material.h"
#include"GameObject.h"
#include "Shader.h"
#include <GL/glew.h> // 包含glew来获取所有的必须OpenGL头文件
#include "TLCore.h"

Material::Material(const char* vertexPath, const char* fragmentPath)
{
	RenderCallback = nullptr;
	shader = new Shader(vertexPath, fragmentPath);
}

Material::Material()
{
	RenderCallback = nullptr;
	shader = new Shader(SHADER_PATH"default.vert", SHADER_PATH"default.frag");
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
	glDrawElements(GL_TRIANGLES, m->GetSize(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Material::SetRenderCallback(std::function<void(GameObject*, Shader*, Material*)> f)
{
	RenderCallback = f;
}