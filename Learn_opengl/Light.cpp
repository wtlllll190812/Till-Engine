#include"Light.h"
#include<string>
REGISTER(Light);


Light::Light(float _intensity, glm::vec3 _color) 
{
	intensity = _intensity;
	color = _color;
}

Light::Light()
{
}

Light::~Light()
{
	auto i = TLEngineCG::lights.begin();
	while (i != TLEngineCG::lights.end())
	{
		if (*i == this)
			TLEngineCG::lights.erase(i);
	}
}

TLxml* Light::Serialize()
{
	auto xml = new TLxml("Light");
	xml->pRoot->SetAttribute("guid", std::to_string(guid));
	xml->pRoot->SetAttribute("intensity", std::to_string(intensity));
	xml->AddChild(TLxml::Serialize(color, "color")->pRoot);
	return xml;
}

void Light::Instantiate(TiXmlNode* xml)
{
	auto element = xml->ToElement();
	guid = std::stoi(element->Attribute("guid"));
	intensity = std::stof(element->Attribute("intensity"));
	color = TLxml::DeSerialize(xml->FirstChild());
}

void Light::Awake()
{
	TLEngineCG::lights.push_back(this);
}
