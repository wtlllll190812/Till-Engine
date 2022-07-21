#pragma once
#include "Singleton.h"
#include <map>
#include <string>
#include <vector>
typedef void* (*PTRCreateObject)(void);



//反射注册宏
#define REFLECTION(className,tag)													\
	className *Creator##className()													\
	{																				\
		return new className;														\
	}																				\
	RegisterAction registerAction##className(										\
		#className,new Reflection(#className,(PTRCreateObject)Creator##className,ReflectionTag::##tag))

enum class ReflectionTag
{
	Component,
	GameObject,
	Material
};
struct Reflection
{
	std::string className;
	PTRCreateObject createF;
	ReflectionTag tag;
	Reflection(std::string name, PTRCreateObject func, ReflectionTag _tag)
		:className(name), createF(func), tag(_tag)
	{}
};

//反射类
class ReflectionManager : public Singleton<ReflectionManager>
{
private:
	std::map<std::string, Reflection*> classMap;
	std::vector<std::string> members;
	std::multimap<ReflectionTag, std::string> memberByTag;
public:
	ReflectionManager();
	void* getClassByName(std::string className);
	const std::vector<std::string>& GetAllMember() const { return members; }
	void registClass(std::string name, Reflection* method);
	
	const std::multimap<ReflectionTag, std::string>::iterator GetMemberByTag(ReflectionTag tag) { return memberByTag.find(tag); }
	const int GetMemberCountByTag(ReflectionTag tag)const { return memberByTag.count(tag); }
};


//注册动作类
class RegisterAction
{
public:
	RegisterAction(std::string className, Reflection* ptrCreateFn)
	{
		ReflectionManager::instance().registClass(className, ptrCreateFn);
	}
};


