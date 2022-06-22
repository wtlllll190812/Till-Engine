#pragma once

#include "Component.hpp"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GameObject;
class Transform :public Component
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
	Transform(glm::vec3, GameObject*);
	~Transform();

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
	void Translate(glm::vec3, float);
};

const glm::vec3 Transform::forward = glm::vec3(0.0f, 0.0f, -1.0f);
const glm::vec3 Transform::back = glm::vec3(0.0f, 0.0f, 1.0f);
const glm::vec3 Transform::left = glm::vec3(-1.0f, 0.0f, 0.0f);
const glm::vec3 Transform::right = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 Transform::up = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 Transform::down = glm::vec3(0.0f, -1.0f, 0.0f);

Transform::Transform(GameObject* gameobject) :Component(gameobject)
{
	position = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(0, 0, 0);
}

Transform::Transform(glm::vec3 pos, GameObject* gameobject) :Component(gameobject)
{
	position = pos;
}

Transform::~Transform()
{
}

glm::vec3 Transform::GetFront()
{
	glm::vec3 front;
	front.x = cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.z));
	front.y = sin(glm::radians(rotation.z));
	front.z = sin(glm::radians(rotation.x)) * cos(glm::radians(rotation.z));
	return glm::normalize(front);
}

glm::vec3 Transform::GetRight()
{
	return glm::normalize(glm::cross(GetFront(), Transform::up));
}

glm::vec3 Transform::GetUp()
{
	return glm::normalize(glm::cross(GetRight(), GetFront()));
}

void Transform::Translate(float dis)
{
	position += dis * GetFront();
}

void Transform::Translate(glm::vec3 direct, float dis)
{
	position += dis * direct;
}