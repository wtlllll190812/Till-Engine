#include"Light.h"
#include<string>
Light::Light(float _intensity, glm::vec3 _color, GameObject* g) :Component(g)
{
	intensity = _intensity;
	TLEngineCG::lights.push_back(this);
	color = _color;
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
	auto xml = new TLxml("camera");
	xml->pRoot->SetAttribute("guid", std::to_string(guid));
	xml->pRoot->SetAttribute("intensity", std::to_string(intensity));
	xml->AddChild(TLxml::Serialize(color, "color")->pRoot);
	return xml;
}
