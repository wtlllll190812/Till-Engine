#pragma once
class Time
{
public:
	friend class GameLoop;


	/// <summary>
	/// 时间流失的速度
	/// </summary>
	static float timeScale;
	/// <summary>
	/// 游戏开始运行后的时间
	/// </summary>
	static float GetTime() { return time; }
	/// <summary>
	/// 游戏开始运行后的时间
	/// </summary>
	static float GetUnscaledTime() { return unscaledTime; }
	/// <summary>
	/// 最近一次fixedTime的时间
	/// </summary>
	static float GetFixedTime() { return fixedTime; }
	/// <summary>
	/// 完成上一帧所用时间
	/// </summary>
	static float GetDeltaTime() { return deltaTime; }
	/// <summary>
	/// 完成上一帧所用时间(不受timescale影响)
	/// </summary>
	static float GetUnscaledDeltaTime() { return unscaledDeltaTime; }
	/// <summary>
	/// 游戏开始之后的帧数
	/// </summary>
	static float GetFrameCount() { return frameCount; }

private:

	static float time;

	static float unscaledTime;

	static float fixedTime;

	static float deltaTime;

	static float unscaledDeltaTime;

	static float frameCount;
};

