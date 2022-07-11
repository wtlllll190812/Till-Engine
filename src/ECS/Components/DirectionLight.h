#pragma once
#include "Light.h"


class DirectionLight:public Light
{
public:
	COMPONENTNAME(DirectionLight)

	DirectionLight();
	~DirectionLight();

	virtual float GetAtten(glm::vec3 objPos)const override { return 1.0f; };
	virtual void Instantiate(TiXmlNode*) override;
	virtual TLxml* Serialize() override;
	virtual void GuiDisPlay() override;
};
