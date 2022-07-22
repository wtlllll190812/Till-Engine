#pragma once
#include "ImguiLayer.h"
#include "KeyEvent.h"
#include "MouseEvent.h"
#include <memory>

class Scene;
class GameObject;
class Camera;
class EditorLayer:public ImguiLayer
{
public:
	EditorLayer(std::shared_ptr<Scene> s);
	~EditorLayer();

	void OnUpdate()override;

	//设置当前场景
	void SetCurrentScene(Scene* s);
	
	//获取场景摄像机
	Camera* GetEditorCamera();

	bool OnMouseMovedEvent(MouseMovedEvent& e)override;
	bool OnMouseScrolledEvent(MouseScrolledEvent& e)override;

private:
	std::shared_ptr<Scene> currentScene;
	std::shared_ptr<GameObject> selectedObj;
	std::shared_ptr<GameObject> editorCamera;
};

