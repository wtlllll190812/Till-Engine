#pragma once
#include <string>
#include <map>
#include <utility>
#include "Singleton .h"

typedef void *(*PTRCreateObject)(void);

//����ע���
#define REFLECTION(className)                 \
	className *Creator##className()           \
	{                                         \
		return new className;                 \
	}                                         \
	RegisterAction registerAction##className( \
		#className, (PTRCreateObject)Creator##className)

//������
class Reflection : public Singleton<Reflection>
{
private:
	std::map<std::string, PTRCreateObject> m_classMap;

public:
	Reflection();
	void *getClassByName(std::string className);
	void registClass(std::string name, PTRCreateObject method);
};

//ע�ᶯ����
class RegisterAction
{
public:
	RegisterAction(std::string className, PTRCreateObject ptrCreateFn)
	{
		Reflection::instance().registClass(className, ptrCreateFn);
	}
};
