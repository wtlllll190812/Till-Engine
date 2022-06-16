#include "Camera.h"

Camera::Camera(Screen* s,GameObject* gameobject) :Component(std::string("Camera"),gameobject), currentScreen(s)
{

}

Camera::~Camera()
{

}

void Camera::OnUpdate()
{
}

void Camera::OnAdd()
{
}

void Camera::OnRemove()
{
}

glm::mat4 Camera::GetViewMatrix()
{
	glm::vec3 position = gameobject->transform->position;
	glm::vec3 front= gameobject->transform->GetFront();
	glm::vec3 up = gameobject->transform->GetUp();
	
	return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::GetProjMatrix()
{
	return glm::perspective(fov, (float)currentScreen->width / (float)currentScreen->heigth, 0.1f, 100.0f);
}

