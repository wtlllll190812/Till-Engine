#pragma once
#include "Layer.h"
#include "KeyEvent.h"
#include "MouseEvent.h"
#include "ApplicationEvent.h"

#include <vector>
#include <memory>

class GuiWindow;
class ImguiLayer :public Layer
{
public:
	ImguiLayer();
	~ImguiLayer();
	void OnAttack()override;
	void OnDetach()override;
	void OnUpdate()override;
	void OnEvent(EventBase& event)override;
	void RegisterGuiWindow(std::shared_ptr<GuiWindow>);
private:
	bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
	bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
	bool OnMouseMovedEvent(MouseMovedEvent& e);
	bool OnMouseScrolledEvent(MouseScrolledEvent& e);
	bool OnKeyPressedEvent(KeyPressedEvent& e);
	bool OnKeyReleasedEvent(KeyReleasedEvent& e);
	bool OnKeyTypedEvent(KeyPressedEvent& e);
	bool OnWindowResizeEvent(WindowResizeEvent& e);
private:
	std::vector<std::shared_ptr<GuiWindow>> uiWindows;
	float mTime = 0;
};
