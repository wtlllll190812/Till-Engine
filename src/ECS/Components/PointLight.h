#pragma once
#include "Light.h"


class PointLight :public Light
{
public:
	COMPONENTNAME(PointLight)

	PointLight();
	~PointLight();
	virtual float GetAtten(glm::vec3 objPos)const override;
	virtual void Instantiate(TiXmlNode*) override;
	virtual TLxml* Serialize() override;
private:
	static float constant;
	static float linear;
	static float quadratic;
};
