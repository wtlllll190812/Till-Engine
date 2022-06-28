#include "Renderer.h"
#include<iostream>
REGISTER(Renderer);

Renderer::Renderer(Mesh* m, Material* mater) 
{
	mesh = m;
	material = mater;
}

Renderer::Renderer()
{
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

void Renderer::Instantiate(TiXmlNode* xml)
{
	auto element = xml->ToElement();
	guid = std::stoi(element->Attribute("guid"));
}	
