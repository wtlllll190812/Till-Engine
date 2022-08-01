#pragma once
#include<functional>

class GameLoop
{
public:
	GameLoop(int);
	~GameLoop();
	bool endLoop;

	/// <summary>
	/// 设置回调
	/// </summary>
	void SetAwakeCallback(std::function<void()>);

	/// <summary>
	/// 设置回调
	/// </summary>
	void SetUpdateCallback(std::function<void()> );

	/// <summary>
	/// 设置回调
	/// </summary>
	void SetFixedUpdateCallback(std::function<void()>);

	/// <summary>
	/// 设置回调
	/// </summary>
	void SetLateUpdateCallback(std::function<void()>);

	/// <summary>
	/// 开始游戏循环
	/// </summary>
	void StartLoop();
	float GetFPS();

private:
	/// <summary>
	/// 初始化回调
	/// </summary>
	std::function<void()> Awake;
	/// <summary>
	/// update回调
	/// </summary>
	std::function<void()> Update;
	/// <summary>
	/// fixedupdate回调
	/// </summary>
	std::function<void()> FixedUpdate;
	/// <summary>
	/// lateUpdate回调
	/// </summary>
	std::function<void()> LateUpdate;
	// void (*OnEnabled)();
	// void (*OnDisabled)();

	int frame;
};
