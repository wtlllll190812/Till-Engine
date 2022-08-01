#pragma once
#include "Light.h"
#include <glm/glm.hpp>

class SpotLight:public Light
{
public:
	COMPONENTNAME(SpotLight)
	SpotLight();
	~SpotLight();

	virtual float GetAtten(glm::vec3 objPos)const override { return 1; }
	
	inline float GetCutoffInside()const { return cutoffInside; }
	inline float GetCutoffOutside()const { return cutoffOutside; }
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
	float cutoffInside;
	float cutoffOutside;
};
