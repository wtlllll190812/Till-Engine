#pragma once
#include <string>
#include "Component.h"

class Screen;
class Camera :public Component
{
public:
	/// <summary>
	/// 视角大小
	/// </summary>
	float fov = 120.0f;

	Camera(Screen*);
	Camera();
	~Camera();

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

private:
	/// <summary>
	/// 当前窗口
	/// </summary>
	Screen* currentScreen;

	/// <summary>
	/// 序列化
	/// </summary>
	virtual TLxml* Serialize() override;

	/// <summary>
	/// 通过xml实例化
	/// </summary>
	/// <param name=""></param>
	virtual void Instantiate(TiXmlNode*) override;
};
