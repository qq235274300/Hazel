#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Hazel {



	class Renderer
	{
	public:
		static void BeginScene(OrthographicsCamera& camera);
		static void EndScene();
		//Ŀǰһ����Ⱦ������˲���(Shader),�������� ���մ���һ��ģ�ͼ���
		static void Submit(const Ref<Shader>& shader,const Ref<VertexArray>& vertexArray,glm::mat4 transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* s_SceneData;
	};


}