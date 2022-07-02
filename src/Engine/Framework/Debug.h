#pragma once
#include "spdlog/spdlog.h"
#include "TillPch.h"

class Debug
{
public:
	static std::stringstream appLogOss;
	static void Init();

	inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return engineLog; }
	inline static std::shared_ptr<spdlog::logger>& GetAppLogger() { return appLog; }

private:
	static std::shared_ptr<spdlog::logger> engineLog;
	static std::shared_ptr<spdlog::logger> appLog;
};
