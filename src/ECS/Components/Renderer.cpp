#include "Renderer.h"
#include "RenderSystem.h"
#include "AssetImporter.h"
#include "TLCore.h"
#include "imgui.h"
#include "Reflection.h"
#include "Material.h"
#include "Debug.h"
#include <map>
REFLECTION(Renderer, Component);

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Draw()
{
	if (material != nullptr && mesh != nullptr)
		material->Draw(gameobject, mesh);
	else
		Debug::GetAppLogger()->error("Can not find material or mesh");
}

void Renderer::Awake()
{
	RenderSystem::instance().RegisterComponent(this);
}

void Renderer::GuiDisPlay()
{
	static bool inited=false;
	static std::vector<const char*> matList;
	static std::vector<const char*> meshList;
	static int currentMesh = 0;
	static int currentMat = 0;

	if (!inited)
	{
		auto start = ReflectionManager::instance().GetMemberStartByTag(ReflectionTag::Material);
		int count = ReflectionManager::instance().GetMemberCountByTag(ReflectionTag::Material);
		for (int k = 0; k != count; k++, start++)
		{
			if (start->second == material->matName)
				currentMat = k;
			matList.push_back(start->second.c_str());
		}
		for (auto &it : AssetImporter::buildinModels) 
		{
			static int index = 0;
			if (it.first+"/"+ it.first+".obj" == modelPath)
				currentMesh = index;
			meshList.push_back(it.first.c_str());
			index++;
		}
		inited = true;
	}
	
	int premat = currentMat;
	ImGui::Combo("Material", &currentMat, &matList[0], matList.size());
	if (premat != currentMat)
	{
		ChangeMaterial(std::static_pointer_cast<Material>(ReflectionManager::instance().GetInstanceByName(matList[currentMat])));
		UpdateNode();
	}

	int premesh = currentMesh;
	ImGui::Combo("Mesh", &currentMesh, &meshList[0], meshList.size());
	if (premesh != currentMesh)
	{
		mesh = AssetImporter::GetMeshByName(meshList[currentMesh]);
		std::string meshName = meshList[currentMesh];
		modelPath = meshName + "/" + meshName + ".obj";
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
