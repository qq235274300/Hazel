#pragma once
#include "Hazel/Layer.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"

//ImGuiLayer Use to Debug & always draw last;

namespace Hazel
{
	class HAZEL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();


		void OnAttach()override;
		void OnDetach()override;
		virtual void OnImGuiRender() override;
	
		void Begin();
		void End();
	private:
		float m_Time = 0.f;

	};

};




