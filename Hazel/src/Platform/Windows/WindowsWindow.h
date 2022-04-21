#pragma once

#include "Hazel/Window.h"
#include <GLFW/glfw3.h>

namespace Hazel
{

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		// Í¨¹ý Window ¼Ì³Ð
		virtual void OnUpdate() override;

		inline unsigned int GetWidth()const override {return m_Data.Width;}
		inline unsigned int GetHeight()const override { return m_Data.Height; }

		//WindowAttributes
		inline void SetEventCallback(const EventCallbackFn& callback)override {m_Data.EventCallback = callback;}
		void SetVsync(bool enabled) override;
		bool GetVsync()const override;
	private:
		virtual void Init(const  WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;
		struct  WindowData
		{	
			std::string Title;
			unsigned int Width,Height;
			bool VSync;

			EventCallbackFn EventCallback;		
		};

		WindowData m_Data;

		
	};


};

