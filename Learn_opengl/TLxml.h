#pragma once
#include <string>
#include <tinyxml.h>
#include <glm/glm.hpp>

class TLxml
{
public:
	TiXmlElement* pRoot;


	TLxml(std::string, std::string);
	TLxml(std::string);
	~TLxml();

	void AddChild(TiXmlElement*);
	void Save() { pDoc->SaveFile(path); }
	static TLxml* Serialize(glm::vec3&, std::string);
	static glm::vec3 DeSerialize(TiXmlNode*);
private:
	std::string path;
	TiXmlDocument* pDoc;
};

