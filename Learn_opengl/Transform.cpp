#include "Transform.h"


const glm::vec3 Transform::forward = glm::vec3(0.0f, 0.0f, -1.0f);
const glm::vec3 Transform::back = glm::vec3(0.0f, 0.0f, 1.0f);
const glm::vec3 Transform::left = glm::vec3(-1.0f, 0.0f, 0.0f);
const glm::vec3 Transform::right = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 Transform::up = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 Transform::down = glm::vec3(0.0f, -1.0f, 0.0f);

Transform::Transform(GameObject* gameobject) :Component(std::string("Transform"), gameobject)
{
	position = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(0, 0, 0);
}


Transform::~Transform()
{
}

void Transform::Translate(glm::vec3 newPosition)
{
	position = newPosition;
}

void Transform::OnAdd()
{

}

void Transform::OnUpdate()
{

}

void Transform::OnRemove()
{

}