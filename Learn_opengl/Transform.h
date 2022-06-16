#pragma once

#include "Component.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GameObject;
class Transform:public Component
{
public:
	static const glm::vec3 forward;
	static const  glm::vec3 back;
	static const  glm::vec3 left;
	static const  glm::vec3 right;
	static const  glm::vec3 up;
	static const  glm::vec3 down;


	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Transform(GameObject*);
	~Transform();

	void OnUpdate()override;
	void OnAdd()override;
	void OnRemove()override;

	/// <summary>
	/// 获取向前方向
	/// </summary>
	glm::vec3 GetFront();

	/// <summary>
	/// 获取向右方向
	/// </summary>
	glm::vec3 GetRight();

	/// <summary>
	/// 获取向上方向
	/// </summary>
	glm::vec3 GetUp();
	
	/// <summary>
	/// 向前移动
	/// </summary>
	void Translate(float);

	/// <summary>
	/// 向某个方向移动
	/// </summary>
	void Translate(glm::vec3,float);
};