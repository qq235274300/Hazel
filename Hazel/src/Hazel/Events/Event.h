#pragma once

#include "hzpch.h"
#include "Hazel/Core.h"




namespace Hazel
{
	enum class EventType
	{
		None = 0,
		WindowClose,WindowResize,WindowFocus,WindowLostFocus,WindowMoved,
		AppTick,AppUpdate,AppRender,
		KeyPressed,KeyReleased,KeyTyped,
		MouseButtonPressed,MouseButtonReleased, MouseMoved, MouseSrolled
	};

	enum EventCategory
	{	
		None = 0 ,
		EventCategoryApplication = BIT(0),
		EventCategoryInput       = BIT(1) ,
		EventCategoryKeyboard    = BIT(2) ,
		EventCategoryMouse       = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};
	//##表示连接 ，#表示转换为字符串
	#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType(){return EventType::##type;}\
									virtual EventType  GetEventType()const override {return GetStaticType();}\
									virtual const char* GetName()const override{return #type;} 
	
	#define EVENT_CLASS_CATEGORY(category) virtual int GetEventCategoryFlags()const override{return category;}

	class HAZEL_API Event
	{
	public:
		virtual EventType GetEventType()const = 0;
		virtual const char* GetName()const = 0;
		virtual int GetEventCategoryFlags()const = 0;
		virtual std::string ToString()const {return GetName();}

	public:
		inline bool IsInCategory(EventCategory Category)
		{
			return GetEventCategoryFlags() & Category;
		}

		bool m_Handled = false;
	};
	

	class EventDispatcher
	{
	public:
		template<typename T>
		using EventFn = std::function<bool(T&)>;

		EventDispatcher(Event& event): m_Event(event){}

		template<typename T>
		bool Dispatcher(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event );
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;	

	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os<<e.ToString();
	}
	
};