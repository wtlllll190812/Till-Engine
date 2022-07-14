#pragma once
#include "TLxml.h"
#include <string>
#include <vector>
#include <memory>

class Camera;
class GameObject;
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
	std::shared_ptr<GameObject> Find(std::string);

	void AddGameObject(std::shared_ptr<GameObject> gObj) { gameobjects.push_back(gObj); }
public:
	/// <summary>
	/// 场景中物体的集合
	/// </summary>
	std::vector<std::shared_ptr<GameObject>> gameobjects; //临时,之后改为私有
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
