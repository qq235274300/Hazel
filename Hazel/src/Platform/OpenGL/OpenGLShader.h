#pragma once

#include "Hazel/Renderer/Shader.h"
#include <glm/glm.hpp>
typedef unsigned int GLenum;

namespace Hazel
{

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filePath);
		OpenGLShader(const std::string& name,const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual~OpenGLShader();

		virtual const std::string& GetName()const override {return m_Name;}
		virtual void Bind()const override;
		virtual void UnBind()const override;

		void UploadUniformInt1(const std::string& name, int value);

		void UploadUniformFloat1(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

		void UploadUniformMat3(const std::string& name, const glm::vec3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		std::string ReadShaderFromFile(const std::string& filePath);
		void Compile(const std::unordered_map<GLenum, std::string>& shaders);
		std::string m_Name;
	private:
		uint32_t m_RendererID;
	};



}