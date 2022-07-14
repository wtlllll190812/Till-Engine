#include"Material.h"
#include"GameObject.h"
#include "Shader.h"
#include <GL/glew.h>
#include "TLCore.h"
#include "Mesh.h"


Material::Material()
{
}

Material::~Material()
{
}

void Material::Render(GameObject* object, shared_ptr<Mesh> mesh)
{
	glBindVertexArray(mesh->VAO);
	shader->Use();
	if (RenderCallback != nullptr)
		RenderCallback(object, shader, this);
	glDrawElements(GL_TRIANGLES, mesh->GetSize(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}