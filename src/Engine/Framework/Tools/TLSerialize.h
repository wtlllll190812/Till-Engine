#pragma once
#include <string>
#include <tinyxml.h>
#include <glm/glm.hpp>

class TiXmlElement;
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
	void Save() { file->SaveFile(path); }

	/// <summary>
	/// 获取根节点
	/// </summary>
	inline TiXmlElement* GetRoot() { return root; }
private:
	std::string path;
	TiXmlDocument* file;
	TiXmlElement* root;
};
class TLSerialize
{
public:
	static TiXmlElement* Serialize(glm::vec3& vector, std::string name);
	static glm::vec3 DeSerialize(TiXmlElement* xml);

};

/// <summary>
/// 可序列化对象接口
/// </summary>
class Serializable
{
public:
	virtual TiXmlElement* Serialize(std::string name="Default") = 0;
	virtual void DeSerialize(TiXmlElement*) = 0;
};