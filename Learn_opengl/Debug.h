#pragma once
#include "spdlog/spdlog.h"
#include <sstream>
#include<memory>

class Debug
{
public:
	static std::ostringstream appLogOss;
	static void Init();

	inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return engineLog; }
	inline static std::shared_ptr<spdlog::logger>& GetAppLogger() { return appLog; }
	
private:
	static std::shared_ptr<spdlog::logger> engineLog;
	static std::shared_ptr<spdlog::logger> appLog;
};

