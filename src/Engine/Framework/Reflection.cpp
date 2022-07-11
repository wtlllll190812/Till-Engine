#include "Reflection.h"

Reflection::Reflection()
{
}

//通过类名称字符串获取类的实例
void* Reflection::getClassByName(std::string className)
{
	std::map<std::string, PTRCreateObject>::const_iterator iter;
	iter = classMap.find(className);
	if (iter == classMap.end())
	{
		return NULL;
	}
	else
	{
		return iter->second();
	}
}

//将给定的类名称字符串和对应的创建类对象的函数保存到map中
void Reflection::registClass(std::string name, PTRCreateObject method)
{
	members.push_back(name.c_str());
	classMap.insert(std::pair<std::string, PTRCreateObject>(name, method));
}