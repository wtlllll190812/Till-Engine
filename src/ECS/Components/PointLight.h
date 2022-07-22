#pragma once
#include "Light.h"


class PointLight :public Light
{
public:
	COMPONENTNAME(PointLight)

	PointLight();
	~PointLight();
	virtual float GetAtten(glm::vec3 objPos)const override;
	virtual void GuiDisPlay() override;

	/// <summary>
	/// 序列化
	/// </summary>
	virtual TiXmlElement* Serialize(std::string name = "Default") override;

	/// <summary>
	/// 反序列化
	/// </summary>
	virtual void DeSerialize(TiXmlElement*) override;
public:
	float range;
private:
	static float constant;
	static float linear;
	static float quadratic;
};
