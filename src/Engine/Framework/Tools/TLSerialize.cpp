#include "TLSerialize.h"
#include <iostream>
#include <fstream>


TLSerializeFile::TLSerializeFile(std::string p, std::string n)
{
	path = p;
	std::ifstream f(path.c_str());

	if (f.good())
	{
		file.LoadFile(path);
		root = file.RootElement();
	}
	else
	{
		root = new TiXmlElement(n);
		file.LinkEndChild(root);
		file.SaveFile(path);
	}
}

TLSerializeFile::~TLSerializeFile()
{
}


TiXmlElement* TLSerialize::Serialize(glm::vec3& vector, std::string name)
{
	auto node = new TiXmlElement(name);
	node->SetAttribute("x", std::to_string(vector.x));
	node->SetAttribute("y", std::to_string(vector.y));
	node->SetAttribute("z", std::to_string(vector.z));
	return node;
}

glm::vec3 TLSerialize::DeSerialize(TiXmlElement* node)
{
	glm::vec3 res = glm::vec3();
	res.x = std::stof(node->Attribute("x"));
	res.y = std::stof(node->Attribute("y"));
	res.z = std::stof(node->Attribute("z"));
	return res;
}

void TLSerialize::UpdateNode(glm::vec3& vector, TiXmlElement* node)
{
	node->SetAttribute("x", std::to_string(vector.x));
	node->SetAttribute("y", std::to_string(vector.y));
	node->SetAttribute("z", std::to_string(vector.z));
}
