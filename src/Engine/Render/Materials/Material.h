#pragma once
#include "TLEngineCG.h"
#include <memory>
#include <functional>
#include <string>
#include "TLCore.h"
#include "OnGui.h"

class GameObject;
class Shader;
class Mesh;
class Material:public IGuiDisplay
{
public:
	Shader* shader;
	std::string matName;
	/// <summary>
	/// 渲染队列次序
	/// </summary>
	int renderQueueIndex = (int)RendererQueue::Geometry;

public:
	Material();
	~Material();

	void Draw(GameObject*, std::shared_ptr<Mesh>);
	virtual void DrawFunc(GameObject* gObj,std::shared_ptr<Mesh> mesh) = 0;
	virtual void Init(GameObject*, std::shared_ptr<Mesh> mesh) = 0;

	// 通过 IGuiDisplay 继承
	virtual void GuiDisPlay() override;
private:
	bool inited;
};