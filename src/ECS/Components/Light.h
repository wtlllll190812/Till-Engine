#pragma once
#include <glm/glm.hpp>
#include "Component.h"

class GameObject;
class Light : public Component
{
public:
	Light(float, glm::vec3);
	Light();
	~Light();

	COMPONENTNAME(Light)
	/// <summary>
	/// 光的强度
	/// </summary>
	float intensity;

	/// <summary>
	/// 光的颜色
	/// </summary>
	glm::vec3 color;

	/// <summary>
	/// 刚添加时
	/// </summary>
	virtual void Awake() override;

	/// <summary>
	/// 获取光的衰减值
	/// </summary>
	virtual float GetAtten(glm::vec3 objPos)=0;
};