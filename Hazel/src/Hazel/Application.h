
/*
*  This Application is Base Class For App Application
* 
*/
#pragma once
#include "Core.h"
#include "Window.h"
#include "Hazel/LayerStack.h"
#include "Events/ApplicationEvent.h"

#include "Hazel/ImGui/ImGuiLayer.h"
#include "Hazel/Renderer/Shader.h"
#include "Hazel/Renderer/Buffer.h"
#include "Hazel/Renderer/VertexArray.h"

#include "Hazel/Renderer/OrthographicCamera.h"

namespace Hazel
{
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	public:
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static  Application& Get(){return *m_Instance;}
		inline Window& GetWindow(){return *m_Window;}
		
	private:
		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;

		//Timestep
		float LastFrameTime = 0.f;
		
		
	private:
		static Application* m_Instance;
	};

	//Define In Client
	Application* CreateApplication();


}

