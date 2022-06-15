#pragma once
#include"Component.h"
#include <string>


class Screen;
class GameObject;
class Camera:public Component
{
public:
	Camera(Screen*, GameObject*);
	~Camera();
	void OnUpdate()override;
	void OnAdd()override;
	void OnRemove()override;
private:
	Screen* currentScreen;
};