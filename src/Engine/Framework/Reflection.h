#pragma once
#include "Singleton .h"
#include "TillPch.h"

typedef void* (*PTRCreateObject)(void);

//反射注册宏
#define REFLECTION(className)                 \
	className *Creator##className()           \
	{                                         \
		return new className;                 \
	}                                         \
	RegisterAction registerAction##className( \
		#className, (PTRCreateObject)Creator##className)

//反射类
class Reflection : public Singleton<Reflection>
{
private:
	std::map<std::string, PTRCreateObject> m_classMap;

public:
	Reflection();
	void* getClassByName(std::string className);
	void registClass(std::string name, PTRCreateObject method);
};

//注册动作类
class RegisterAction
{
public:
	RegisterAction(std::string className, PTRCreateObject ptrCreateFn)
	{
		Reflection::instance().registClass(className, ptrCreateFn);
	}
};
