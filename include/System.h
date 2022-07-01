#pragma once
#include"Singleton .h"

class Component;
class System
{
public:
	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;
	virtual void RegisterComponent(Component*) = 0;
	virtual void RemoveComponent(Component*) = 0;
};
