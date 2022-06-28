#pragma once
#include "TLxml.h"
#include <string>

class GameObject;
class Component
{
public:
	GameObject* gameobject;

	Component(GameObject* gameobject) :gameobject(gameobject) {}
	
	/// <summary>
	/// 刷新时
	/// </summary>
	virtual void OnUpdate() {};
	
	/// <summary>
	/// 添加时
	/// </summary>
	virtual void OnAdd() {};
	
	/// <summary>
	/// 移除时
	/// </summary>
	virtual void OnRemove() {};

	/// <summary>
	/// 序列化
	/// </summary>
	virtual TLxml* Serialize() = 0;
};