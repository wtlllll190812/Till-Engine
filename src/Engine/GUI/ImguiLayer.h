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
	void OnEvent(EventBase& event)override;
	void RegisterGuiWindow(std::shared_ptr<GuiWindow>);
	virtual void OnUpdate()override;

protected:
	void RenderStart();
	void RenderEnd();
	static void ImGuiInit();

private:
	virtual bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
	virtual bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
	virtual bool OnMouseMovedEvent(MouseMovedEvent& e);
	virtual bool OnMouseScrolledEvent(MouseScrolledEvent& e);
	virtual bool OnKeyPressedEvent(KeyPressedEvent& e);
	virtual bool OnKeyReleasedEvent(KeyReleasedEvent& e);
	virtual bool OnKeyTypedEvent(KeyPressedEvent& e);
	virtual bool OnWindowResizeEvent(WindowResizeEvent& e);

protected:
	std::vector<std::shared_ptr<GuiWindow>> uiWindows;
	float mTime = 0;
};
