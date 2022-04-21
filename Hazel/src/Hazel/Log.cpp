#include "hzpch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Hazel
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		//��ӡ��ʽΪ ʱ�� logger�� ��������
		spdlog::set_pattern("%^[%T] %n: %v%$");

		//����Logger ������ ��ӡ���������� info ������ȫ����Ϣ����ӡpp
		s_CoreLogger = spdlog::stdout_color_mt("Hazel");
		s_CoreLogger->set_level(spdlog::level::info);

		s_ClientLogger = spdlog::stderr_color_mt("App");
		s_ClientLogger->set_level(spdlog::level::info);
	}
}

