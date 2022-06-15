#pragma once
#include <string>


class GameObject;
class Component
{
public:
	GameObject* gameobject;
	const std::string componentName;

	Component(std::string name,GameObject* gameobject) :componentName(name),gameobject(gameobject) {}
	virtual void OnUpdate()=0;
	virtual void OnAdd()=0;
	virtual void OnRemove()=0;
};

