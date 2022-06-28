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
	static TLxml* Serialize(glm::vec3&,std::string);
private:
	std::string path;
	TiXmlDocument* pDoc;
};

