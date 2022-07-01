#pragma once
#include <glm/glm.hpp>
#include "Component.h"

class GameObject;
class Light : public Component
{
public:
	Light(float, glm::vec3);
	Light();
	~Light();

	/// <summary>
	/// 锟斤拷锟角匡拷锟�
	/// </summary>
	float intensity;

	/// <summary>
	/// 锟斤拷锟斤拷锟缴�
	/// </summary>
	glm::vec3 color;

	/// <summary>
	/// 锟斤拷锟叫伙拷
	/// </summary>
	virtual TLxml *Serialize() override;

	/// <summary>
	/// 通锟斤拷xml实锟斤拷锟斤拷
	/// </summary>
	virtual void Instantiate(TiXmlNode *) override;

	/// <summary>
	/// 锟斤拷锟斤拷锟斤拷时
	/// </summary>
	virtual void Awake() override;
};