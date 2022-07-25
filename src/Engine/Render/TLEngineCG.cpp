#include"TLEngineCG.h"
#include <glm/glm.hpp>
#include "Window.h"
#include "Application.h"
#include "FrameBuffer.h"
#include "MatShadowCaster.h"

std::vector<Light*> TLEngineCG::lights = std::vector<Light*>();
FrameBuffer* TLEngineCG::shadowBuffer = Application::instance().mWindows->AddFrameBuffer(BufferType::Both);
Material* TLEngineCG::sadowCaster=new MatShadowCaster();

void TLEngineCG::AddLight(Light* light)
{
	lights.push_back(light);
}
