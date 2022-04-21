#pragma once

#ifdef  HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
	Hazel::Log::Init();
	/*HZ_CORE_WARN("Log System Init");
	int a = 5;
	std::string s = "xxxxaa";
	HZ_INFO("Hello ,Var={0},{1}",a,s);*/
	
	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}


#endif //  HZ_PLATFORM_WINDOWS

