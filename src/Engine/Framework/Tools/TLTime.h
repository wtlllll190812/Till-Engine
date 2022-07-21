#pragma once
class TLTime
{
public:
	friend class GameLoop;

	/// <summary>
	/// 时间流失的速度
	/// </summary>
	static double timeScale;
	/// <summary>
	/// 游戏开始运行后的时间
	/// </summary>
	static double GetTime() { return time; }
	/// <summary>
	/// 游戏开始运行后的时间
	/// </summary>
	static double GetUnscaledTime() { return unscaledTime; }
	/// <summary>
	/// 最近一次fixedTime的时间
	/// </summary>
	static double GetFixedTime() { return fixedTime; }
	/// <summary>
	/// 完成上一帧所用时间
	/// </summary>
	static double GetDeltaTime() { return deltaTime; }
	/// <summary>
	/// 完成上一帧所用时间(不受timescale影响)
	/// </summary>
	static double GetUnscaledDeltaTime() { return unscaledDeltaTime; }
	/// <summary>
	/// 游戏开始之后的帧数
	/// </summary>
	static double GetFrameCount() { return frameCount; }

private:
	static double time;

	static double unscaledTime;

	static double fixedTime;

	static double deltaTime;

	static double unscaledDeltaTime;

	static double frameCount;
};
