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
		auto start = ReflectionManager::instance().GetMemberStartByTag(ReflectionTag::Material);
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
		ChangeMaterial(std::static_pointer_cast<Material>(ReflectionManager::instance().GetInstanceByName(stest[current])));
		UpdateNode();
	}
}

bool Renderer::operator>(const Renderer& r)
{
	return r.material->renderQueueIndex > material->renderQueueIndex;
}

TiXmlElement* Renderer::Serialize(std::string name)
{
	if (m_node == nullptr)
	{
		m_node = new TiXmlElement(GetName());
	}
	m_node->SetAttribute("guid", std::to_string(guid));
	m_node->SetAttribute("modelPath", modelPath);
	m_node->SetAttribute("materialName", material->matName);
	return m_node;
}

void Renderer::DeSerialize(TiXmlElement* node)
{
	m_node = node;
	guid = std::stoi(node->Attribute("guid"));
	modelPath = node->Attribute("modelPath");
	auto mat = ReflectionManager::instance().CreateClassByName(node->Attribute("materialName"));
	material = std::shared_ptr<Material>((Material*)mat);
	mesh = AssetImporter::LoadMeshs(MODEL_PATH + modelPath)[0];
}

void Renderer::UpdateNode()
{
	m_node->SetAttribute("modelPath", modelPath);
	m_node->SetAttribute("materialName", material->matName);
}

void Renderer::ChangeMaterial(std::shared_ptr<Material> mat)
{
	material = mat;
}
