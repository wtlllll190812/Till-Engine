#pragma once
#include "Light.h"


class DirectionLight:public Light
{
public:
	COMPONENTNAME(DirectionLight)

	DirectionLight();
	~DirectionLight();

	virtual float GetAtten(glm::vec3 objPos)const override { return 1.0f; };
	virtual void GuiDisPlay() override;

	/// <summary>
	/// 序列化
	/// </summary>
	virtual TiXmlElement* Serialize(std::string name = "Default") override;

	/// <summary>
	/// 反序列化
	/// </summary>
	virtual void DeSerialize(TiXmlElement*) override;
};
