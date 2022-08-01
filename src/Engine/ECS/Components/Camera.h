#pragma once
#include <string>
#include "Component.h"

class Camera : public Component
{
public:
	COMPONENTNAME(Camera)

		Camera();
	~Camera();

	/// <summary>
	/// 视角大小
	/// </summary>
	float fov = 120.0f;

	/// <summary>
	/// 获取观察矩阵
	/// </summary>
	/// <returns>观察矩阵</returns>
	glm::mat4 GetViewMatrix();

	/// <summary>
	/// 获取透视矩阵
	/// </summary>
	/// <returns>获取透视矩阵</returns>
	glm::mat4 GetProjMatrix();

	inline void SetAspectRatio(float value)
	{
		aspectRatio = value;
	}

	inline float GetAspectRatio()
	{
		return aspectRatio;
	}

	/// <summary>
	/// 序列化
	/// </summary>
	virtual TiXmlElement* Serialize(std::string name = "Default") override;

	/// <summary>
	/// 反序列化
	/// </summary>
	virtual void DeSerialize(TiXmlElement*) override;
	virtual void UpdateNode() override;

private:
	float aspectRatio = 4.0f/3;

private:
	virtual void GuiDisPlay() override;
};
