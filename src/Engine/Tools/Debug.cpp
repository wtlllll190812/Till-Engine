#include "Debug.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/ostream_sink.h "
#include "spdlog/sinks/rotating_file_sink.h"


std::shared_ptr<spdlog::logger> Debug::engineLog=spdlog::stdout_color_mt("Till Engine");
std::shared_ptr<spdlog::logger> Debug::appLog = spdlog::stdout_color_mt("App");;
std::stringstream Debug::appLogOss;

void Debug::Init()
{
	std::vector<spdlog::sink_ptr> sinks;

	engineLog->set_level(spdlog::level::trace);	
	engineLog->sinks().push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/engineLog.txt", 1024 * 1024, 5, false));
	engineLog->set_pattern("%^[%T] %n: %v%@%s%#%$");

	appLog->set_level(spdlog::level::trace);
	appLog->sinks().push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/appLog.txt", 1024 * 1024, 5, false));
	appLog->sinks().push_back(std::make_shared<spdlog::sinks::ostream_sink_mt>(appLogOss));
	appLog->set_pattern("%^[%T] %n: %v%@%s%#%$");
}

