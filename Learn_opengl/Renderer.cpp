#include "Renderer.h"
#include "RenderSystem.h"
#include<iostream>
#include<vector>
REGISTER(Renderer);

Renderer::Renderer(Mesh* m, Material* mater) 
{
	mesh = shared_ptr<Mesh>(m);
	material = shared_ptr<Material>(mater);
}

Renderer::Renderer()
{
	 mesh = shared_ptr<Mesh>(new Mesh());
	 material = shared_ptr<Material>(new Material());
}

Renderer::~Renderer()
{
}

void Renderer::Render()
{
	material->Render(mesh);
	//RenderSystem::instance().RegisterComponent(this);
}

void Renderer::Awake()
{
	RenderSystem::instance().RegisterComponent(this);
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
