#pragma once
#include"Component.h"

class Behaviour:public Component
{
	// Í¨¹ý Component ¼Ì³Ð
	virtual void Instantiate(TiXmlNode*) override;
	virtual TLxml* Serialize() override;

	virtual void Update() {};
	virtual void FixedUpdate() {};
	virtual void LateUpdate() {};
};