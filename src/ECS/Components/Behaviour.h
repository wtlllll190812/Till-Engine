#pragma once
#include "Component.h"

class Behaviour : public Component
{
	COMPONENTNAME(Behaviour)

	virtual void Update() {};
	virtual void FixedUpdate() {};
	virtual void LateUpdate() {};


	// 通过 Component 继承
	virtual TiXmlElement* Serialize(std::string name = "Default") override;

	virtual void DeSerialize(TiXmlElement*) override;
};