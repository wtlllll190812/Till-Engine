#include "Behaviour.h"
#include "Reflection.h"

REFLECTION(Behaviour, Component);
void Behaviour::Instantiate(TiXmlNode*)
{
}

TLxml* Behaviour::Serialize()
{
	return nullptr;
}