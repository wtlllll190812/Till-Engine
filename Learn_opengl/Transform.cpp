#include "Transform.h"

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

TLxml* Transform::Serialize()
{
	auto xml = new TLxml("trasnsform");
	xml->pRoot->SetAttribute("guid",std::to_string(guid));
	xml->AddChild(TLxml::Serialize(position, "position")->pRoot);
	xml->AddChild(TLxml::Serialize(rotation, "rotation")->pRoot);
	xml->AddChild(TLxml::Serialize(scale, "scale")->pRoot);
	return xml;
}
