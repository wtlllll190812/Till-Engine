#pragma once
#include "EventBase.h"
#include <string>

class Layer
{
public:
	Layer(const std::string& name = "Layer");
	virtual ~Layer() { OnDetach(); };

	virtual void OnAttack() {}
	virtual void OnDetach() {}
	virtual void OnUpdate() {}
	virtual void OnEvent(EventBase& event) {}

	inline const std::string& GetName()const { return mDebugName; }

private:
	std::string mDebugName;
};