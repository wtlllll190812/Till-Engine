#pragma once
#include "TLxml.h"
#include <string>
#include <vector>
#include "GameObject.h"

class Camera;
class Scene
{
public:
	Camera* camera;


	/// <summary>
	/// 读取并初始化场景
	/// </summary>
	/// <param name="">场景文件路径</param>
	Scene(std::string);
	~Scene();

	/// <summary>
	/// 保存场景
	/// </summary>
	void Save();
	
	/// <summary>
	/// 在场景中寻找对象
	/// </summary>
	/// <param name="">对象名称</param>
	GameObject* Find(std::string);	
	
	/// <summary>
	/// 场景中物体的集合
	/// </summary>
	std::vector<GameObject*> gameobjects;//临时,之后改为私有
private:
	/// <summary>
	/// 场景文件路径
	/// </summary>
	std::string path;
	
	/// <summary>
	/// 场景文件对象
	/// </summary>
	TLxml xml;
};
