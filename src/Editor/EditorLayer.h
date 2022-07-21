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
	void SetScene(Scene* s);
	Camera* GetEditorCamera();

	bool OnMouseMovedEvent(MouseMovedEvent& e)override;
	bool OnMouseScrolledEvent(MouseScrolledEvent& e)override;

private:
	std::shared_ptr<Scene> currentScene;
	std::shared_ptr<GameObject> editorCamera;
	std::shared_ptr<GameObject> currentObj;
};

