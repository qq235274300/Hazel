#pragma once

// ����ͶӰCamera��2D��, ��תֻ����Z��
#include <glm/glm.hpp>

namespace Hazel
{
	class OrthographicsCamera
	{
	public:
		OrthographicsCamera(float left, float right, float bottom, float top);
		
		const glm::vec3 GetPosition()const { return m_Position; }
		void SetPosition(const glm::vec3& position) {m_Position = position; RecalculateViewMatrix();}
		
		float GetRotation()const {return m_Rotation;}
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix();}
		
		const glm::mat4& GetProjectionMatrix()const {return m_ProjectionMatrix;}
		const glm::mat4& GetViewMatrix()const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix()const { return m_ViewProjectionMatrix; }

	private:
		//Set Transform����Ҫ��д����VP����
		void RecalculateViewMatrix();
	private:
		//
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
		

		//Camera Transform
		glm::vec3 m_Position = {0.f,0.f,0.f};
		float m_Rotation = 0.0f;
		
	};



}