#pragma once
#include "ImguiLayer.h"
#include "KeyEvent.h"
#include "MouseEvent.h"
#include <memory>

class Scene;
class GameObject;
class Camera;
/// <summary>
/// 编辑器层级
/// </summary>
class EditorLayer:public ImguiLayer
{
public:
	EditorLayer(std::shared_ptr<Scene> s);
	~EditorLayer();

	void OnUpdate()override;

	/// <summary>
	/// 设置当前场景
	/// </summary>
	void SetCurrentScene(Scene* s);
	
	/// <summary>
	/// 获取编辑器摄像机
	/// </summary>
	Camera* GetEditorCamera();

	/// <summary>
	/// 鼠标移动事件
	/// </summary>
	bool OnMouseMovedEvent(MouseMovedEvent& e)override;
	
	/// <summary>
	/// 鼠标滚轮事件
	/// </summary>
	bool OnMouseScrolledEvent(MouseScrolledEvent& e)override;

private:
	/// <summary>
	/// 当前场景
	/// </summary>
	std::shared_ptr<Scene> mCurrentScene;
	
	/// <summary>
	/// 选中的物体
	/// </summary>
	std::shared_ptr<GameObject> selectedObj;
	
	/// <summary>
	/// 场景摄像机
	/// </summary>
	std::shared_ptr<GameObject> editorCamera;
};

