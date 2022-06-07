#include "hzpch.h"
#include "Application.h"

#include "Hazel/Log.h"
#include "Hazel/Input.h"
#include "Hazel/Core/Timestep.h"

#include "Hazel/Renderer/Renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Hazel
{
	#define BIND_EVENT_FN(x)  std::bind(&Application::x,this,std::placeholders::_1)
	
	 Application*  Application::m_Instance  = nullptr;
	

	
	Application::Application()
	{
		HZ_CORE_ASSERT(!m_Instance, "Application Already exist!");
		m_Instance= this;

		//Create Window
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));	
		m_Window->SetVsync(true);

		//Set Renderer Porperties
		Renderer::Init();

		//Create Layer
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		
	}
	Application::~Application()
	{

	}
	void Application::Run()
	{	
		while (m_Running)
		{		
			//计算每帧花费时间
			float time = (float)glfwGetTime();
			Timestep ts = time - LastFrameTime;
			LastFrameTime = time;
			
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate(ts);
			}
			//To do in RenderThread;
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();


			m_Window->OnUpdate();			
		};
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatcher<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		HZ_CORE_INFO("{0}",e);
		//Layer 由上至下检测Event是否被处理 处理了就跳出 
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.m_Handled)
			{
				break;
			}
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}