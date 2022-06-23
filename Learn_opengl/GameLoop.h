#pragma once
#include <ctime>


class GameLoop
{
public:
	GameLoop(int);
	~GameLoop();

private:
	void (*Awake)();
	void (*Update)();
	void (*FixedUpdate)();
	void (*LateUpdate)();
	void (*OnEnabled)();
	void (*OnDisabled)();
	
	int frame;
};

