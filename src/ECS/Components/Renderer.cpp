#include "Renderer.h"
#include "RenderSystem.h"
#include "AssetImporter.h"
#include "TLCore.h"
#include "imgui.h"
#include "Reflection.h"
#include "Material.h"
REFLECTION(Renderer, Component);

Renderer::Renderer()
{
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
	xml->pRoot->SetAttribute("modelPath", modelPath);
	xml->pRoot->SetAttribute("materialName", material->matName);
	return xml;
}

void Renderer::Instantiate(TiXmlNode* xml)
{
	auto element = xml->ToElement();
	guid = std::stoi(element->Attribute("guid"));
	modelPath = element->Attribute("modelPath");
	auto mat = ReflectionManager::instance().getClassByName(element->Attribute("materialName"));
	material = std::shared_ptr<Material>((Material*)mat);
	mesh = AssetImporter::LoadMeshs(MODEL_PATH+modelPath)[0];
}

void Renderer::GuiDisPlay()
{
	ImGui::Text("Material");
	ImGui::Text("Mesh");
}

bool Renderer::operator>(const Renderer& r)
{
	return r.material->renderQueueIndex > material->renderQueueIndex;
}