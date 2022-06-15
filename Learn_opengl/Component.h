#pragma once
#include <string>


class GameObject;
class Component
{
public:
	GameObject* owner;
	const std::string componentName;

	Component(std::string name,GameObject* gameobject) :componentName(name),owner(gameobject) {}
	virtual void OnUpdate()=0;
	virtual void OnAdd()=0;
	virtual void OnRemove()=0;
};

