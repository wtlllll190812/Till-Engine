#pragma once
#include <string>
#include <tinyxml.h>
#include <glm/glm.hpp>

class TLxml
{
public:
	TiXmlElement* pRoot;

	/// <summary>
	/// 构造函数
	/// </summary>
	/// <param name="">路径</param>
	/// <param name="">根元素名称</param>
	TLxml(std::string, std::string);
	/// <summary>
	/// 构造非文件节点
	/// </summary>
	/// <param name="">根元素名称</param>
	TLxml(std::string);
	~TLxml();

	/// <summary>
	/// 添加子节点
	/// </summary>
	void AddChild(TiXmlElement*);
	
	/// <summary>
	/// 保存文件
	/// </summary>
	void Save() { pDoc->SaveFile(path); }
	
	/// <summary>
	/// 序列化向量
	/// </summary>
	/// <param name="">向量</param>
	/// <param name="">节点名</param>
	static TLxml* Serialize(glm::vec3&, std::string);
	
	/// <summary>
	/// 反序列化向量
	/// </summary>
	/// <param name="">向量</param>
	/// <returns>节点名</returns>
	static glm::vec3 DeSerialize(TiXmlNode*);
private:
	std::string path;
	TiXmlDocument* pDoc;
};

/// <summary>
/// 可序列化对象接口
/// </summary>
class Serializable
{
	virtual TLxml* Serialize()=0;
	virtual void DeSerialize(TiXmlNode*)=0;
};