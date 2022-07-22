#include "Renderer.h"
#include "RenderSystem.h"
#include "AssetImporter.h"
#include "TLCore.h"
#include "imgui.h"
#include "Reflection.h"
#include "Material.h"
#include "Debug.h"
REFLECTION(Renderer, Component);

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Draw()
{
	material->Draw(gameobject, mesh);
}

void Renderer::Awake()
{
	RenderSystem::instance().RegisterComponent(this);
}

void Renderer::GuiDisPlay()
{
	static bool inited=false;
	static std::vector<const char*> stest;

	if (!inited)
	{
		auto start = ReflectionManager::instance().GetMemberByTag(ReflectionTag::Material);
		int count = ReflectionManager::instance().GetMemberCountByTag(ReflectionTag::Material);
		for (int k = 0; k != count; k++, start++)
		{
			stest.push_back(start->second.c_str());
		}
		Debug::GetEngineLogger()->warn(stest.size());
		inited = true;
	}

	static int current = 0;
	int pre = current;
	ImGui::Combo("combo", &current, &stest[0], stest.size());
	if (pre != current)
	{
		ChangeMaterial((Material*)ReflectionManager::instance().getClassByName(stest[current]));
	}
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

void Renderer::ChangeMaterial(Material* mat)
{
	material = std::shared_ptr<Material>(mat);
}
