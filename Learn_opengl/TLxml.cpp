#include "TLxml.h"
#include <iostream>
#include <fstream>


TLxml::TLxml(std::string p, std::string n)
{
    path = p;
    std::ifstream f(path.c_str());
    pDoc = new TiXmlDocument();

    if (f.good())
    {
        pDoc->LoadFile(path);
        pRoot = pDoc->RootElement();
    }
    else
    {
        pRoot = new TiXmlElement(n);
        pDoc->LinkEndChild(pRoot);
        pDoc->SaveFile(path);
    }
}

TLxml::TLxml(std::string n)
{
    pRoot = new TiXmlElement(n);
}

TLxml::~TLxml()
{
    
    if (pDoc != nullptr)
        pDoc->SaveFile(path);
    /*{
        pDoc->SaveFile(path);
        delete pDoc;
    }
    delete pRoot;*/
}

void TLxml::AddChild(TiXmlElement* child)
{
    pRoot->LinkEndChild(child);
}

TLxml* TLxml::Serialize(glm::vec3& vector,std::string name)
{
    auto xml = new TLxml(name);
    xml->pRoot->SetAttribute("x", std::to_string(vector.x));
    xml->pRoot->SetAttribute("y", std::to_string(vector.y));
    xml->pRoot->SetAttribute("z", std::to_string(vector.z));
    return xml;
}

glm::vec3 TLxml::DeSerialize(TiXmlNode* xml)
{
    auto element = xml->ToElement();
    glm::vec3 res=glm::vec3();
    res.x = std::stof(element->Attribute("x"));
    res.y = std::stof(element->Attribute("y"));
    res.z = std::stof(element->Attribute("z"));
    return res;
}


