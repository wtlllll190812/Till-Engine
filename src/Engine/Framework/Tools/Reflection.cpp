#include "Reflection.h"

ReflectionManager::ReflectionManager()
{
}

//通过类名称字符串获取类的实例
void* ReflectionManager::CreateClassByName(std::string className)
{
	std::map<std::string, Reflection*>::const_iterator iter;
	iter = classMap.find(className);
	if (iter == classMap.end())
	{
		return NULL;
	}
	else
	{
		return iter->second->createF();
	}
}

std::shared_ptr<void> ReflectionManager::GetInstanceByName(std::string className)
{
	std::map<std::string, Reflection*>::const_iterator iter;
	iter = classMap.find(className);
	if (iter == classMap.end())
	{
		return NULL;
	}
	else
	{
		return iter->second->getInstance();
	}
}

//将给定的类名称字符串和对应的创建类对象的函数保存到map中
void ReflectionManager::RegistClass(std::string name, Reflection* method)
{
	members.push_back(name.c_str());
	memberByTag.insert(std::pair<ReflectionTag,std::string>(method->tag,method->className));
	classMap.insert(std::pair<std::string, Reflection*>(name, method));
}