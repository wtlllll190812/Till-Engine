#pragma once
#include "Reflection.h"
#include "TLxml.h"
#include "TillPch.h"

class GameObject;
class Component
{
public:
	const virtual std::string GetName() const = 0;

	GameObject* gameobject;
	int guid;

	Component() : gameobject(nullptr), guid(GetHash()) {}

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

#define COMPONENTNAME(name)  static std::string GetStaticName() { return #name; }				\
							 virtual const std::string GetName() const override { return #name; }