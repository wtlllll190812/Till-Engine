#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Screen.h"

REFLECTION(Camera);
Camera::Camera(Screen* s) :currentScreen(s)
{
}

Camera::Camera()
{
	componentName = "Camera";
	currentScreen = &Screen::instance();
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
	return glm::perspective(fov, (float)currentScreen->width / (float)currentScreen->heigth, 0.1f, 100.0f);
}

TLxml* Camera::Serialize()
{
	auto xml = new TLxml(componentName);
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