#include "DirectionLight.h"
#include "imgui.h"
#include "Reflection.h"

REFLECTION(DirectionLight, Component);
DirectionLight::DirectionLight()
{
}

DirectionLight::~DirectionLight()
{
}

void DirectionLight::GuiDisPlay()
{
	float col[3] = { color.x,color.y,color.z };
	ImGui::DragFloat("Intensity", &intensity);
	ImGui::ColorEdit3("Color", col);
	color = glm::vec3(col[0], col[1], col[2]);
}

TiXmlElement* DirectionLight::Serialize(std::string name)
{
	auto sceneFile = new TiXmlElement(GetName());
	sceneFile->SetAttribute("guid", std::to_string(guid));
	sceneFile->SetAttribute("intensity", std::to_string(intensity));
	sceneFile->LinkEndChild(TLSerialize::Serialize(color, "color"));
	return sceneFile;
}

void DirectionLight::DeSerialize(TiXmlElement* node)
{
	guid = std::stoi(node->Attribute("guid"));
	intensity = std::stof(node->Attribute("intensity"));
	color = TLSerialize::DeSerialize(node);
}