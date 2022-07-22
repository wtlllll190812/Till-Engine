#include "SpotLight.h"
#include "Reflection.h"
#include "imgui.h"
#include "Reflection.h"

REFLECTION(SpotLight, Component);
SpotLight::SpotLight()
{
}

SpotLight::~SpotLight()
{
}

void SpotLight::GuiDisPlay()
{
	float col[3] = { color.x,color.y,color.z };
	ImGui::DragFloat("Intensity", &intensity);
	ImGui::DragFloat("CutoffOutside", &cutoffOutside);
	ImGui::DragFloat("CutoffInside", &cutoffInside);
	ImGui::ColorEdit3("Color", col);
	color = glm::vec3(col[0], col[1], col[2]);
}

TiXmlElement* SpotLight::Serialize(std::string name)
{
	auto xml = new TiXmlElement(GetName());
	xml->SetAttribute("guid", std::to_string(guid));
	xml->SetAttribute("intensity", std::to_string(intensity));
	xml->LinkEndChild(TLSerialize::Serialize(color, "color"));
	return xml;
}

void SpotLight::DeSerialize(TiXmlElement* node)
{
	guid = std::stoi(node->Attribute("guid"));
	intensity = std::stof(node->Attribute("intensity"));
	color = TLSerialize::DeSerialize(node->FirstChildElement());
}
