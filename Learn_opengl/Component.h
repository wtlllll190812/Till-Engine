#pragma once
#include "TLxml.h"
#include <string>
#include <functional>


class GameObject;
class Component
{
public:
	GameObject* gameobject;
	int guid;

	Component(GameObject* gameobject) :gameobject(gameobject),guid(GetHash()) {}
	
	/// <summary>
	/// 刷新时
	/// </summary>
	virtual void OnUpdate() {};
	
	/// <summary>
	/// 添加时
	/// </summary>
	virtual void Awake() {};
	
	/// <summary>
	/// 移除时
	/// </summary>
	virtual void OnRemove() {};

	/// <summary>
	/// 序列化
	/// </summary>
	virtual TLxml* Serialize() = 0;

	/// <summary>
	/// 获取哈希值
	/// </summary>
	int GetHash()
	{
		std::hash<Component*> h;
		return (h(this));
	}
};

