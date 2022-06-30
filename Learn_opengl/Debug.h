#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include<memory>

class Debug
{
public:
	static void Init();
	inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return engineLog; }
	inline static std::shared_ptr<spdlog::logger>& GetAppLogger() { return appLog; }
	
private:
	static std::shared_ptr<spdlog::logger> engineLog;
	static std::shared_ptr<spdlog::logger> appLog;
};

