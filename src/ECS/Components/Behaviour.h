#pragma once
#include "Component.h"

class Behaviour : public Component
{
	// 通过 Component 继承
	virtual void Instantiate(TiXmlNode *) override;
	virtual TLxml *Serialize() override;

	virtual void Update(){};
	virtual void FixedUpdate(){};
	virtual void LateUpdate(){};
};