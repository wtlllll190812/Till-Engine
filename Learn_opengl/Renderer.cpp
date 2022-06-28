#include "Renderer.h"
#include<iostream>

Renderer::Renderer(Mesh* m, Material* mater, GameObject* g) :Component(g)
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

void Renderer::Awake()
{
	std::cout << "sdsd" << std::endl;
	renderQueue.push(dynamic_cast<Renderer*>(this));
}

TLxml* Renderer::Serialize()
{
	auto xml = new TLxml("Renderer");
	xml->pRoot->SetAttribute("guid", std::to_string(guid));
	return xml;
}
