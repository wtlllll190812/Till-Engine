#include"Light.h"
#include "TLEngineCG.h"


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

void Light::Awake()
{
	TLEngineCG::lights.push_back(this);
}