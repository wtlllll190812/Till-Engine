#pragma once
#include <string>
#include <functional>
#include "Reflection.h"
#include "TLxml.h"

class GameObject;
class Component
{
public:
	std::string componentName;
	GameObject* gameobject;
	int guid;

	Component() :gameobject(nullptr), guid(GetHash()),componentName("Component") {}

	/// <summary>
	/// 通过xml实例化
	/// </summary>
	/// <param name=""></param>
	virtual void Instantiate(TiXmlNode*) = 0;

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