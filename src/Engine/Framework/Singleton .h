#pragma once

template <class T>
class Singleton
{
public:
	static T &instance()
	{
		static T *instance = new T();
		return *instance;
	}
	Singleton() {}
};