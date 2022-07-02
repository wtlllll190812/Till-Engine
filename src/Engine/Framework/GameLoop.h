#pragma once
#include <ctime>
#include "TillPch.h"

class GameLoop
{
public:
	GameLoop(int);
	~GameLoop();
	bool endLoop;

	/// <summary>
	/// 设置回调
	/// </summary>
	void SetAwakeCallback(void (*Awake)());

	/// <summary>
	/// 设置回调
	/// </summary>
	void SetUpdateCallback(void (*Update)());

	/// <summary>
	/// 设置回调
	/// </summary>
	void SetFixedUpdateCallback(void (*FixedUpdate)());

	/// <summary>
	/// 设置回调
	/// </summary>
	void SetLateUpdateCallback(void (*LateUpdate)());

	/// <summary>
	/// 开始游戏循环
	/// </summary>
	void StartLoop();
	float GetFPS();

private:
	/// <summary>
	/// 初始化回调
	/// </summary>
	void (*Awake)();
	/// <summary>
	/// update回调
	/// </summary>
	void (*Update)();
	/// <summary>
	/// fixedupdate回调
	/// </summary>
	void (*FixedUpdate)();
	/// <summary>
	/// lateUpdate回调
	/// </summary>
	void (*LateUpdate)();
	// void (*OnEnabled)();
	// void (*OnDisabled)();

	int frame;
};
