#pragma once
#include "TLSerialize.h"
#include <string>
#include <vector>
#include <memory>

class Camera;
class GameObject;
/// <summary>
/// 场景类
/// </summary>
class Scene
{
public:
	/// <summary>
	/// 主摄像机
	/// </summary>
	Camera *mainCamera;

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

	/// <summary>
	/// 添加新物体
	/// </summary>
	void AddGameObject(std::shared_ptr<GameObject> gObj);

public:
	/// <summary>
	/// 场景中物体的集合
	/// </summary>
	std::vector<std::shared_ptr<GameObject>> gameobjects;

private:
	/// <summary>
	/// 场景文件路径
	/// </summary>
	std::string path;

	/// <summary>
	/// 场景文件对象
	/// </summary>
	TLSerializeFile sceneFile;
};
