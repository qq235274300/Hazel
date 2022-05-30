#pragma once
#include "hzpch.h"
#include "Core.h"
#include "Hazel/Events/Event.h"

namespace Hazel
{
	struct WindowProps
	{
		WindowProps(const std::string& title = "Hazel Engine", unsigned int width = 1280, unsigned int height = 720) :
			m_Title(title), m_Width(width), m_Height(height)
		{}

		std::string m_Title;
		unsigned int m_Width;
		unsigned int m_Height;
	};

	//¥ø–È¿‡
	class HAZEL_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		
		virtual ~Window(){}
		
		virtual void OnUpdate() = 0;
		
		virtual unsigned int GetWidth()const = 0;
		virtual unsigned int GetHeight()const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVsync(bool enabled) = 0;
		virtual bool GetVsync()const = 0;

		virtual void* GetNativeWindow()const = 0;

	public:
		static Window* Create(const WindowProps& prop = WindowProps());
	};


}