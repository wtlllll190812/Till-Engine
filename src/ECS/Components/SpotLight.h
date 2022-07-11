#pragma once
#include "Light.h"
#include <glm/glm.hpp>

class SpotLight:public Light
{
public:
	COMPONENTNAME(SpotLight)
	SpotLight();
	~SpotLight();

	virtual void Instantiate(TiXmlNode*) override;
	virtual TLxml* Serialize() override;
	virtual float GetAtten(glm::vec3 objPos)const override { return 1; }
	
	inline float GetCutoffInside()const { return cutoffInside; }
	inline float GetCutoffOutside()const { return cutoffOutside; }
	virtual void GuiDisPlay() override;

public:
	float cutoffInside;
	float cutoffOutside;
};
