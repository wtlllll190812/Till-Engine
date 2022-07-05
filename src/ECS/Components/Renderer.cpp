#include "Renderer.h"
#include "RenderSystem.h"

REFLECTION(Renderer);

Renderer::Renderer(Mesh* m, Material* mater)
{
	mesh = std::shared_ptr<Mesh>(m);
	material = std::shared_ptr<Material>(mater);
}

Renderer::Renderer()
{
	mesh = std::shared_ptr<Mesh>(new Mesh());
	material = std::shared_ptr<Material>(new Material());
}

Renderer::~Renderer()
{
}

void Renderer::Render()
{
	material->Render(gameobject, mesh);
	//RenderSystem::instance().RegisterComponent(this);
}

void Renderer::Awake()
{
	RenderSystem::instance().RegisterComponent(this);
}

TLxml* Renderer::Serialize()
{
	auto xml = new TLxml(GetName());
	xml->pRoot->SetAttribute("guid", std::to_string(guid));
	return xml;
}

void Renderer::Instantiate(TiXmlNode* xml)
{
	auto element = xml->ToElement();
	guid = std::stoi(element->Attribute("guid"));
}

bool Renderer::operator>(const Renderer& r)
{
	return r.material->renderQueueIndex > material->renderQueueIndex;
}