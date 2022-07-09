#include "DirectionLight.h"

REFLECTION(DirectionLight);
DirectionLight::DirectionLight()
{
}

DirectionLight::~DirectionLight()
{
}

TLxml* DirectionLight::Serialize()
{
	auto xml = new TLxml(GetName());
	xml->pRoot->SetAttribute("guid", std::to_string(guid));
	xml->pRoot->SetAttribute("intensity", std::to_string(intensity));
	xml->AddChild(TLxml::Serialize(color, "color")->pRoot);
	return xml;
}

void DirectionLight::Instantiate(TiXmlNode* xml)
{
	auto element = xml->ToElement();
	guid = std::stoi(element->Attribute("guid"));
	intensity = std::stof(element->Attribute("intensity"));
	color = TLxml::DeSerialize(xml->FirstChild());
}
