#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"

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
	glm::vec3 rotation= gameobject->transform->rotation;

	glm::vec3 front,right,up;
	front.x = cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.z));
	front.y = sin(glm::radians(rotation.z));
	front.z = sin(glm::radians(rotation.x)) * cos(glm::radians(rotation.z));
	
	front = glm::normalize(front);
	right = glm::normalize(glm::cross(front, Transform::up));
	up = glm::normalize(glm::cross(right, front));
	
	return glm::lookAt(position, position + front, up);
}
glm::mat4 Camera::GetProjMatrix()
{
	return glm::perspective(fov, (float)currentScreen->width / (float)currentScreen->heigth, 0.1f, 100.0f);
}
//GLfloat yaw = -90.0f;
//GLfloat pitch = 0.0f;
//GLfloat lastX = WIDTH / 2.0;
//GLfloat lastY = HEIGHT / 2.0;
