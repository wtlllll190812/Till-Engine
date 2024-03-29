#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>
#include "Debug.h"

const glm::vec3 Transform::forward = glm::vec3(0.0f, 0.0f, -1.0f);
const glm::vec3 Transform::back = glm::vec3(0.0f, 0.0f, 1.0f);
const glm::vec3 Transform::left = glm::vec3(-1.0f, 0.0f, 0.0f);
const glm::vec3 Transform::right = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 Transform::up = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 Transform::down = glm::vec3(0.0f, -1.0f, 0.0f);

Transform::Transform()
{
	position = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(0, 0, 0);
}

Transform::Transform(glm::vec3 pos, GameObject* gameobject)
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

glm::mat4 Transform::GetModelMatrix()
{
	//平移矩阵
	glm::mat4 translationMatrix = glm::translate(glm::identity<glm::mat4>(), position);
	glm::mat4 rotationMatrix = glm::eulerAngleYXZ(glm::radians(rotation.y),glm::radians(rotation.x), glm::radians(rotation.z));
	glm::mat4 scaleMatrix = glm::scale(glm::identity<glm::mat4>(), scale);

	return translationMatrix * rotationMatrix * scaleMatrix;
}

TiXmlElement* Transform::Serialize(std::string name)
{
	if (m_node == nullptr)
		m_node = new TiXmlElement(GetName());
	m_node->SetAttribute("guid", std::to_string(guid));
	m_node->LinkEndChild(TLSerialize::Serialize(position, "position"));
	m_node->LinkEndChild(TLSerialize::Serialize(rotation, "rotation"));
	m_node->LinkEndChild(TLSerialize::Serialize(scale, "scale"));
	return m_node;
}

void Transform::DeSerialize(TiXmlElement* node)
{
	m_node = node;
	guid = std::stoi(node->Attribute("guid"));
	node = node->FirstChildElement();
	position = TLSerialize::DeSerialize(node);
	node = node->NextSiblingElement();
	rotation = TLSerialize::DeSerialize(node);
	node = node->NextSiblingElement();
	scale = TLSerialize::DeSerialize(node);
}

void Transform::UpdateNode()
{
	if (m_node)
	{
		m_node->SetAttribute("guid", std::to_string(guid));
		auto node = m_node->FirstChildElement();
		TLSerialize::UpdateNode(position, node);
		node = node->NextSiblingElement();
		TLSerialize::UpdateNode(rotation, node);
		node = node->NextSiblingElement();
		TLSerialize::UpdateNode(scale, node);
	}
}

void Transform::GuiDisPlay()
{
	DrawVec3Control("Position", position);
	DrawVec3Control("Rotation", rotation);
	DrawVec3Control("Scale", scale);
	UpdateNode();
}

void Transform::Decompose(glm::mat4 newModel)
{
	glm::quat quaternion;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(newModel, scale, quaternion, position, skew, perspective);

	glm::mat4 rotationMatrix1 = glm::toMat4(quaternion);
	glm::vec3 euler(0, 0, 0);
	glm::extractEulerAngleYXZ(rotationMatrix1, euler.y, euler.x, euler.z);
	rotation.y = glm::degrees(euler.y);
	rotation.x = glm::degrees(euler.x);
	rotation.z = glm::degrees(euler.z);
}
