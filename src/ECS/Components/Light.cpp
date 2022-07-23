#include"Light.h"
#include "TLEngineCG.h"
#include "Application.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GameObject.h"
#include "Transform.h"

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

glm::mat4 Light::GetViewMatrix()
{
	return glm::lookAt(gameobject->transform->position, gameobject->transform->position+gameobject->transform->GetFront(), gameobject->transform->GetUp());
}

glm::mat4 Light::GetProjMatrix()
{
	float near_plane = 1.0f, far_plane = 7.5f;
	return glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
}

void Light::Awake()
{
	TLEngineCG::AddLight(this);
}