#include "TLSerialize.h"
#include <iostream>
#include <fstream>


TLSerializeFile::TLSerializeFile(std::string p, std::string n)
{
	path = p;
	std::ifstream f(path.c_str());
	file = new TiXmlDocument();

	if (f.good())
	{
		file->LoadFile(path);
		root = file->RootElement();
	}
	else
	{
		root = new TiXmlElement(n);
		file->LinkEndChild(root);
		file->SaveFile(path);
	}
}

TLSerializeFile::~TLSerializeFile()
{
}


TiXmlElement* TLSerialize::Serialize(glm::vec3& vector, std::string name)
{
	auto xml = new TiXmlElement(name);
	xml->SetAttribute("x", std::to_string(vector.x));
	xml->SetAttribute("y", std::to_string(vector.y));
	xml->SetAttribute("z", std::to_string(vector.z));
	return xml;
}

glm::vec3 TLSerialize::DeSerialize(TiXmlElement* node)
{
	glm::vec3 res = glm::vec3();
	res.x = std::stof(node->Attribute("x"));
	res.y = std::stof(node->Attribute("y"));
	res.z = std::stof(node->Attribute("z"));
	return res;
}