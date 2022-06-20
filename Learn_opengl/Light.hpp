#pragma once
#include "Component.hpp"
#include <glm/glm.hpp>
#include "TLEngineCG.hpp"

class GameObject;
class Light:public Component
{
public:
	Light(float, glm::vec3,GameObject*);
	~Light();
	float intensity;
	glm::vec3 color;
private:
	
};

Light::Light(float _intensity,glm::vec3 _color,GameObject* g):Component(g)
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