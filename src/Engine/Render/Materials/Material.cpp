#include"Material.h"
#include"GameObject.h"
#include "Shader.h"
#include <GL/glew.h>
#include "TLCore.h"
#include "Mesh.h"


Material::Material()
{
	inited = false;
}

Material::~Material()
{
}

void Material::Render(GameObject* object, shared_ptr<Mesh> mesh)
{
	if (!inited)
	{
		BeforeRender(object, mesh);
		inited = true;
	}
	glBindVertexArray(mesh->VAO);
	shader->Use();
	OnRender(object, mesh);
	glDrawElements(GL_TRIANGLES, mesh->GetSize(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}