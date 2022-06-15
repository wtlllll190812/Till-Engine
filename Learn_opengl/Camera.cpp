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
