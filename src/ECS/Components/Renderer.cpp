#include "Renderer.h"
#include "RenderSystem.h"
#include "AssetImporter.h"
#include "TLCore.h"
REFLECTION(Renderer);


Renderer::Renderer()
{
	material = std::shared_ptr<Material>(new Material());
	mesh = AssetImporter::LoadMeshs(MODEL_PATH"nanosuit/nanosuit.obj")[0];
}

Renderer::~Renderer()
{
}

void Renderer::Render()
{
	material->Render(gameobject, mesh);
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