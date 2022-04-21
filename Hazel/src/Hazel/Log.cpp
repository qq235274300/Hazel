#include "hzpch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Hazel
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		//打印形式为 时间 logger名 具体内容
		spdlog::set_pattern("%^[%T] %n: %v%$");

		//创建Logger 和设置 打印出来的内容 info 基本是全部信息都打印pp
		s_CoreLogger = spdlog::stdout_color_mt("Hazel");
		s_CoreLogger->set_level(spdlog::level::info);

		s_ClientLogger = spdlog::stderr_color_mt("App");
		s_ClientLogger->set_level(spdlog::level::info);
	}
}

