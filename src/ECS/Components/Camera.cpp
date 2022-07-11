#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "Application.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "imgui.h"

REFLECTION(Camera);

Camera::Camera()
{
}

Camera::~Camera()
{
}

glm::mat4 Camera::GetViewMatrix()
{
	glm::vec3 position = gameobject->transform->position;
	glm::vec3 front = gameobject->transform->GetFront();
	glm::vec3 up = gameobject->transform->GetUp();

	return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::GetProjMatrix()
{
	float b = (float)Application::instance().mWindows->GetWidth() / Application::instance().mWindows->GetHeight();
	return glm::perspective(fov, b, 0.1f, 100.0f);
}

TLxml* Camera::Serialize()
{
	auto xml = new TLxml(GetName());
	xml->pRoot->SetAttribute("guid", std::to_string(guid));
	xml->pRoot->SetAttribute("fov", std::to_string(fov));
	return xml;
}

void Camera::Instantiate(TiXmlNode* xml)
{
	auto element = xml->ToElement();
	fov = std::stof(element->Attribute("fov"));
	guid = std::stoi(element->Attribute("guid"));
}

void Camera::GuiDisPlay()
{
	ImGui::DragFloat("FOV",&fov);
}
