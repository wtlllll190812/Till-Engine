#include "Behaviour.h"
#include "Reflection.h"

REFLECTION(Behaviour, Component);

TiXmlElement* Behaviour::Serialize(std::string name)
{
	return nullptr;
}

void Behaviour::DeSerialize(TiXmlElement*)
{
}