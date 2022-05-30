#include "hzpch.h"
#include "OrthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>
namespace Hazel
{
	OrthographicsCamera::OrthographicsCamera(float left, float right, float bottom, float top)
	:m_ProjectionMatrix(glm::ortho(left,right,bottom,top,-1.f,1.f)),m_ViewMatrix(1.f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	void OrthographicsCamera::RecalculateViewMatrix()
	{
		//TRS
		glm::mat4 transform = glm::translate(glm::mat4(1.0f),m_Position) *
		glm::rotate(glm::mat4(1.0f),glm::radians(m_Rotation),glm::vec3(0.f,0.f,1.f));
		
		//����������������ƶ��෴
		m_ViewMatrix = glm::inverse(transform);
		//VP ����
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}