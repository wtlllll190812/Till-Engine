#pragma once

template <class T>
class Singleton
{
public:
	static T& instance()
	{
		static T Instance;
		return Instance;
	}
	Singleton() {}
};