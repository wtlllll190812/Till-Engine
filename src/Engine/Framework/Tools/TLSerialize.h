#pragma once
#include <string>
#include <tinyxml.h>
#include <glm/glm.hpp>

class TLSerializeFile
{
public:
	/// <summary>
	/// 构造函数
	/// </summary>
	/// <param name="">路径</param>
	/// <param name="">根元素名称</param>
	TLSerializeFile(std::string, std::string);
	~TLSerializeFile();

	/// <summary>
	/// 保存文件
	/// </summary>
	void Save()
	{
		file.SaveFile(path);
	}

	/// <summary>
	/// 获取根节点
	/// </summary>
	inline TiXmlElement* GetRoot() { return root; }
private:

	/// <summary>
	/// 文件路径
	/// </summary>
	std::string path;
	
	/// <summary>
	/// 文件对象
	/// </summary>
	TiXmlDocument file;
	
	/// <summary>
	/// 文件根节点
	/// </summary>
	TiXmlElement* root;
};

/// <summary>
/// 常用类的序列化支持
/// </summary>
class TLSerialize
{
public:
	static TiXmlElement* Serialize(glm::vec3& vector, std::string name);
	static glm::vec3 DeSerialize(TiXmlElement* sceneFile);
	static void UpdateNode(glm::vec3& vector, TiXmlElement* node);
};

/// <summary>
/// 可序列化对象接口
/// </summary>
class Serializable
{
public:
	/// <summary>
	/// 序列化节点
	/// </summary>
	TiXmlElement* m_node=nullptr;
public:
	/// <summary>
	/// 序列化
	/// </summary>
	virtual TiXmlElement* Serialize(std::string name="Default") = 0;
	
	/// <summary>
	/// 反序列化
	/// </summary>
	virtual void DeSerialize(TiXmlElement*) = 0;
	
	/// <summary>
	/// 更新序列化节点
	/// </summary>
	virtual void UpdateNode() {};
};