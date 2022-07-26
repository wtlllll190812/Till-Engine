#include"Material.h"
#include"GameObject.h"
#include "Shader.h"
#include <GL/glew.h>
#include "TLCore.h"
#include "Mesh.h"


Material::Material()
{
	shader = nullptr;
	inited = false;
}

Material::~Material()
{
	if(shader!=nullptr)
	delete shader;
}

void Material::Draw(GameObject* object, shared_ptr<Mesh> mesh)
{
	if (!inited)
	{
		Init(object, mesh);
		inited = true;
	}
	glBindVertexArray(mesh->VAO);
	shader->Use();
	DrawFunc(object, mesh);
	glDrawElements(GL_TRIANGLES, mesh->GetSize(), GL_UNSIGNED_INT, 0);
	glDepthMask(GL_TRUE);
	glCullFace(GL_BACK);
	glBindVertexArray(0);
}