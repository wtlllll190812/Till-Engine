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
	Transform* tr = gameobject->transform;
	return glm::lookAt(tr->position + tr->GetFront(), tr->position,  tr->GetUp());
}

glm::mat4 Light::GetOrthoMatrix()
{
	float near_plane = 1.0f, far_plane = 100.0f;
	return glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, near_plane, far_plane);
}

void Light::Awake()
{
	TLEngineCG::AddLight(this);
}