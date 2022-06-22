#pragma once

class GameObject;
class Component
{
public:
	GameObject* gameobject;

	Component(GameObject* gameobject) :gameobject(gameobject) {}
	virtual void OnUpdate() {};
	virtual void OnAdd() {};
	virtual void OnRemove() {};
};