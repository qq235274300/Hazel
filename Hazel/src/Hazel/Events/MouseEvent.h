#pragma once

#include "Event.h"

namespace Hazel
{
	
	class HAZEL_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float mouseX, float mouseY)
		:m_MouseX(mouseX), m_MouseY(mouseY)
		{}

		inline float GetX()const {return m_MouseX;}
		inline float GetY()const { return m_MouseY; }

		virtual std::string ToString()const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent" << m_MouseX << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_MouseX;
		float m_MouseY;
	};

	class HAZEL_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float Xoffset, float Yoffset)
			:m_Xoffset(Xoffset), m_Yoffset(Yoffset)
		{}

		inline float GetXoffset() { return m_Xoffset; }
		inline float GetYoffset() { return m_Yoffset; }

		virtual std::string ToString()const override
		{
			std::stringstream ss;
			ss << " MouseSrolled" << m_Xoffset << m_Yoffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseSrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_Xoffset;
		float m_Yoffset;
	};

	class HAZEL_API MouseButtonEvent : public Event
	{
	public:
		
		inline int GetMouseButton()const {return m_Button;}
		EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput)

	protected:
		MouseButtonEvent(int button): m_Button(button){}


		int m_Button;
	};



	class HAZEL_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button): MouseButtonEvent(button){}


		virtual std::string ToString()const override
		{
			std::stringstream ss;
			ss << " MouseButtonPressedEvent" << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};


	class HAZEL_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

		virtual std::string ToString()const override
		{
			std::stringstream ss;
			ss << " MouseButtonReleased"<< m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

};