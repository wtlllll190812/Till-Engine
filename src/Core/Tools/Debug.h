#pragma once
#include "spdlog/spdlog.h"

class Debug
{
public:
	//applog的字符串流对象,用于编辑器显示
	static std::stringstream appLogOss;
	//初始化debug系统
	static void Init();

	inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return engineLog; }
	inline static std::shared_ptr<spdlog::logger>& GetAppLogger() { return appLog; }

private:
	static std::shared_ptr<spdlog::logger> engineLog;
	static std::shared_ptr<spdlog::logger> appLog;
};