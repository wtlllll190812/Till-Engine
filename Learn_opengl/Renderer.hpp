#pragma once
#include"Component.hpp"
#include"Material.hpp"
#include"Mesh.hpp"

class GameObject;
class Renderer:public Component
{
public:
	Mesh* mesh;
	Material* material;

	Renderer(Mesh* , Material* , GameObject*);
	~Renderer();
	void Render();
};

Renderer::Renderer(Mesh *m,Material *mater,GameObject* g):Component(g)
{
	mesh = m;
	material = mater;
}

Renderer::~Renderer()
{

}

void Renderer::Render()
{
	material->Render(mesh);
}