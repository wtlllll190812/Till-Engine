#pragma once
#include <glm/glm.hpp>
#include "TLEngineCG.h"
#include "Component.h"

class GameObject;
class Light :public Component
{
public:
	Light(float, glm::vec3);
	Light();
	~Light();

	/// <summary>
	/// 光的强度
	/// </summary>
	float intensity;

	/// <summary>
	/// 光的颜色
	/// </summary>
	glm::vec3 color;

	/// <summary>
	/// 序列化
	/// </summary>
	virtual TLxml* Serialize() override;

	// 通过 Component 继承
	virtual void Instantiate(TiXmlNode*) override;

	virtual void Awake() override;
};