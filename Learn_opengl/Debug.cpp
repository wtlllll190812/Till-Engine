#include "Debug.h"


std::shared_ptr<spdlog::logger> Debug::engineLog= spdlog::basic_logger_mt("engineLog", "logs/engineLog.txt");
std::shared_ptr<spdlog::logger> Debug::appLog = spdlog::basic_logger_mt("appLog", "logs/appLog.txt");

void Debug::Init()
{
	spdlog::set_pattern("%^[%T] %n:%v%$");
	engineLog = spdlog::stdout_color_mt("Till Engine");
	engineLog->set_level(spdlog::level::trace);	
	
	appLog = spdlog::stdout_color_mt("App");
	appLog->set_level(spdlog::level::trace);
}

