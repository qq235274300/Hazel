#include <Hazel.h>
#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer():Layer("Example"),m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPostion(0.f), m_CameraRotation(0.f), m_SquarePos(0.f)
	{
		m_VertexArray.reset(Hazel::VertexArray::Create());


		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		Hazel::Ref<Hazel::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));

		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		{
			Hazel::BufferLayout layout = {
				{ Hazel::ShaderDataType::Float3, "a_Position" },
				{ Hazel::ShaderDataType::Float4, "a_Color" }
			};

			vertexBuffer->SetLayout(layout);
		}

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Hazel::Ref<Hazel::IndexBuffer> indexBuffer;
		indexBuffer.reset(Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position =  u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader =  Hazel::Shader::Create("Triangle", vertexSrc, fragmentSrc);

		//Try Render another VAO
		{

			m_SquareVA.reset(Hazel::VertexArray::Create());

			float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.f, 0.f,
			 0.5f, -0.5f, 0.0f, 1.f, 0.f,
			 0.5f,  0.5f, 0.0f, 1.f, 1.f,
			-0.5f,  0.5f, 0.0f, 0.f, 1.f
			};

			Hazel::Ref<Hazel::VertexBuffer> squareVB;
			squareVB.reset(Hazel::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
			squareVB->SetLayout({
				{ Hazel::ShaderDataType::Float3, "a_Position" },
				{ Hazel::ShaderDataType::Float2, "a_TexCoord" }

				});
			m_SquareVA->AddVertexBuffer(squareVB);

			uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
			Hazel::Ref<Hazel::IndexBuffer> squareIB;
			squareIB.reset(Hazel::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
			m_SquareVA->SetIndexBuffer(squareIB);

//*********** This Shader using to render GridUniform Square **********************
			std::string float4ShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;

			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_Transform;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

			std::string float4ShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			uniform vec4 u_Color;
			void main()
			{
				color = u_Color;
			}
		)";

			m_Float4Shader = Hazel::Shader::Create("UniformSuqare", float4ShaderVertexSrc, float4ShaderFragmentSrc);

//*********** This Shader using to render GridUniform Square **********************


//*********** This Shader using to render Texture Square **********************
			/*std::string TexShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			out vec2 v_TexCoord;

			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_Transform;
			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

			std::string TexShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec2 v_TexCoord;
			
			uniform sampler2D u_Texture;
			
			void main()
			{
				color = texture(u_Texture,v_TexCoord);
				
			}
		)";*/

		//m_TexShader = Hazel::Shader::Create("assets/shaders/Texture.glsl");
		
//*********** This Shader using to render Texture Square **********************


		}
		auto m_TexShader = m_ShaderLib.Load("assets/shaders/Texture.glsl");
		m_TexCheckboard = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
		m_TexCherno = Hazel::Texture2D::Create("assets/textures/ChernoLogo.png");
		//std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_TexShader)->Bind();
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_TexShader)->UploadUniformInt1("u_Texture", 0);
	
	}

	void OnUpdate(Hazel::Timestep ts)override
	{
		//Input
		if (Hazel::Input::IsKeyPressed(HZ_KEY_UP))
		{
			m_CameraPostion.y +=  m_CameraMoveSpeed * ts;
		}
		else if(Hazel::Input::IsKeyPressed(HZ_KEY_DOWN))
		{
			m_CameraPostion.y -= m_CameraMoveSpeed * ts ;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_LEFT))
		{
			m_CameraPostion.x -= m_CameraMoveSpeed * ts;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_RIGHT))
		{
			m_CameraPostion.x += m_CameraMoveSpeed * ts;
		}
		if (Hazel::Input::IsKeyPressed(HZ_KEY_Q))
		{
			m_CameraRotation += m_CameraRotSpeed * ts;
		}
		if (Hazel::Input::IsKeyPressed(HZ_KEY_E))
		{
			m_CameraRotation -= m_CameraRotSpeed * ts;
		}

		//Input Model
		if (Hazel::Input::IsKeyPressed(HZ_KEY_W))
		{
			m_SquarePos.y += m_SquareMoveSpeed * ts;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_S))
		{
			m_SquarePos.y -= m_SquareMoveSpeed * ts;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_A))
		{
			m_SquarePos.x -= m_SquareMoveSpeed * ts;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_D))
		{
			m_SquarePos.x += m_SquareMoveSpeed * ts;
		}


		// Render
		Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Hazel::RenderCommand::Clear();

		//CameraMovement
		m_Camera.SetPosition(m_CameraPostion);
		m_Camera.SetRotation(m_CameraRotation);

		//‰÷»æ
		Hazel::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.f),glm::vec3(0.1f));

		for (int x = 0; x < 20; ++x)
		{
			for (int y = 0; y < 20; ++y)
			{
				glm::vec3 pos = glm::vec3(x * 0.11f, y* 0.11f, 0.f);
				glm::mat4 trs = glm::translate(glm::mat4(1.f),pos) * scale;
				if (x % 2 == 0)
				{
					std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_Float4Shader)->UploadUniformFloat4("u_Color", m_BlueColor);	
				}
				else
				{
					std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_Float4Shader)->UploadUniformFloat4("u_Color", m_RedColor);
				}
				Hazel::Renderer::Submit(m_Float4Shader, m_SquareVA,trs);
			}
		}
		//Render Square From Tex
		auto m_TexShader = m_ShaderLib.Get("Texture");

		m_TexCheckboard->Bind();
		Hazel::Renderer::Submit(m_TexShader, m_SquareVA, glm::scale(glm::mat4(1.f), glm::vec3(1.5f)));

		m_TexCherno->Bind();
		Hazel::Renderer::Submit(m_TexShader, m_SquareVA, glm::scale(glm::mat4(1.f), glm::vec3(1.5f)));

		//Render Triangle
		//Hazel::Renderer::Submit(m_Shader, m_VertexArray);

		Hazel::Renderer::EndScene();
	}
	void OnEvent(Hazel::Event& event)override
	{
		//HZ_INFO("{0}",event);
	}

	virtual void OnImGuiRender()override
	{
		ImGui::Begin("Square UI");
		
		ImGui::ColorEdit4("Square Color1",glm::value_ptr(m_RedColor));
		ImGui::ColorEdit4("Square Color2", glm::value_ptr(m_BlueColor));

		ImGui::End();
	}

private:
	Hazel::ShaderLibrary m_ShaderLib;
	Hazel::Ref<Hazel::Shader> m_Shader;
	Hazel::Ref<Hazel::VertexArray> m_VertexArray;

	Hazel::Ref<Hazel::Shader> m_Float4Shader;
	Hazel::Ref<Hazel::VertexArray> m_SquareVA;

	Hazel::Ref<Hazel::Texture2D> m_TexCheckboard;
	Hazel::Ref<Hazel::Texture2D> m_TexCherno;

	Hazel::OrthographicsCamera m_Camera;
	
	glm::vec3 m_CameraPostion;
	float m_CameraMoveSpeed = 1.f;
	float m_CameraRotation;
	float m_CameraRotSpeed = 20.f;

	glm::vec3 m_SquarePos;
	float m_SquareMoveSpeed = 1.f;

	glm::vec4 m_BlueColor = glm::vec4(0.29f,0.f,0.51f,1.f);
	glm::vec4 m_RedColor = glm::vec4(1.f,0.f,0.f,1.f);
};


class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	};
	~Sandbox(){};
};

Hazel::Application* Hazel::CreateApplication()
{
	return  new Sandbox();
}
