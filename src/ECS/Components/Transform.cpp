#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include "imgui.h"
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>


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
	/*glm::mat4 model(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, rotation.x, right);
	model = glm::rotate(model, rotation.y, up);
	model = glm::rotate(model, rotation.z, back);
	model = glm::scale(model, scale);
	return model;*/
	//平移矩阵
	glm::mat4 translationMatrix = glm::translate(glm::identity<glm::mat4>(), position);
	glm::mat4 rotationMatrix = glm::eulerAngleYXZ(glm::radians(rotation.y),glm::radians(rotation.x), glm::radians(rotation.z));
	glm::mat4 scaleMatrix = glm::scale(glm::identity<glm::mat4>(), scale);

	return translationMatrix * rotationMatrix * scaleMatrix;
}

TLxml* Transform::Serialize()
{
	auto xml = new TLxml("Transform");
	xml->pRoot->SetAttribute("guid", std::to_string(guid));
	xml->AddChild(TLxml::Serialize(position, "position")->pRoot);
	xml->AddChild(TLxml::Serialize(rotation, "rotation")->pRoot);
	xml->AddChild(TLxml::Serialize(scale, "scale")->pRoot);
	return xml;
}

void Transform::Instantiate(TiXmlNode* xml)
{
	auto element = xml->ToElement();
	guid = std::stoi(element->Attribute("guid"));
	element = element->FirstChildElement();
	position = TLxml::DeSerialize(element);
	element = element->NextSiblingElement();
	rotation = TLxml::DeSerialize(element);
	element = element->NextSiblingElement();
	scale = TLxml::DeSerialize(element);
}

void Transform::GuiDisPlay()
{
	float pos[3] = { position.x,position.y,position.z };
	float rot[3] = { rotation.x,rotation.y,rotation.z };
	float sca[3] = { scale.x,scale.y,scale.z };

	ImGui::DragFloat3("Position", pos);
	position = glm::vec3(pos[0], pos[1], pos[2]);
	ImGui::DragFloat3("Rotation", rot);
	rotation = glm::vec3(rot[0], rot[1], rot[2]);
	ImGui::DragFloat3("Scale", sca);
	scale = glm::vec3(sca[0], sca[1], sca[2]);
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
	euler.y = glm::degrees(euler.y);
	euler.x = glm::degrees(euler.x);
	euler.z = glm::degrees(euler.z);
}
