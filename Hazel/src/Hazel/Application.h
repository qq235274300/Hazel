
/*
*  This Application is Base Class For App Application
* 
*/
#pragma once
#include "Core.h"


namespace Hazel
{
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	//Define In Client
	Application* CreateApplication();
}

