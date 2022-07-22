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

void Renderer::GuiDisPlay()
{
	ImGui::Text("Material");
	ImGui::Text("Mesh");
}

bool Renderer::operator>(const Renderer& r)
{
	return r.material->renderQueueIndex > material->renderQueueIndex;
}

TiXmlElement* Renderer::Serialize(std::string name)
{
	auto node = new TiXmlElement(GetName());
	node->SetAttribute("guid", std::to_string(guid));
	node->SetAttribute("modelPath", modelPath);
	node->SetAttribute("materialName", material->matName);
	return node;
}

void Renderer::DeSerialize(TiXmlElement* node)
{
	guid = std::stoi(node->Attribute("guid"));
	modelPath = node->Attribute("modelPath");
	auto mat = ReflectionManager::instance().getClassByName(node->Attribute("materialName"));
	material = std::shared_ptr<Material>((Material*)mat);
	mesh = AssetImporter::LoadMeshs(MODEL_PATH + modelPath)[0];
}
