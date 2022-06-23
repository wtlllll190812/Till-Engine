#pragma once
#include <ctime>


class GameLoop
{
public:
	GameLoop(int);
	~GameLoop();
	bool endLoop;

	void SetAwakeCallback(void (*Awake)());
	void SetUpdateCallback(void (*Update)());
	void SetFixedUpdateCallback(void (*FixedUpdate)());
	void SetLateUpdateCallback(void (*LateUpdate)());
	void StartLoop();

private:
	void (*Awake)();
	void (*Update)();
	void (*FixedUpdate)();
	void (*LateUpdate)();
	//void (*OnEnabled)();
	//void (*OnDisabled)();
	
	int frame;
};

