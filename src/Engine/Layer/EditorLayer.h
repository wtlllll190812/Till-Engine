#pragma once
#include "ImguiLayer.h"
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
private:
	std::shared_ptr<Scene> currentScene;
	std::shared_ptr<GameObject> editorCamera;
	std::shared_ptr<GameObject> currentObj;
};

