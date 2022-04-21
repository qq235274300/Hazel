#include "hzpch.h"
#include "Application.h"

#include "Hazel/Log.h"


#include <glad/glad.h>

namespace Hazel
{
	#define BIND_EVENT_FN(x)  std::bind(&Application::x,this,std::placeholders::_1)
	
	 Application*  Application::m_Instance  = nullptr;
	
	Application::Application()
	{
		HZ_CORE_ASSERT(!m_Instance, "Application Already exist!");
		m_Instance= this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));	
	}
	Application::~Application()
	{

	}
	void Application::Run()
	{	
		while (m_Running)
		{
			
				glClearColor(1, 0, 1, 1);
				glClear(GL_COLOR_BUFFER_BIT);
				//Update
				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate();
				}
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