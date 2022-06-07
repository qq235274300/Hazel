#pragma once
#include <string>

namespace Hazel
{

	class Shader
	{
	public:
		
		virtual ~Shader() = default;

		virtual const std::string& GetName()const  = 0;

		virtual void Bind()const = 0;
		virtual void UnBind()const = 0;

		static Ref<Shader> Create(const std::string& filePath);
		static Ref<Shader> Create(const std::string& name,const std::string& vertexSrc, const std::string& fragmentSrc);
	};

	class ShaderLibrary
	{
	public:
		void Add(const std::string& name,Ref<Shader> shader);
		void Add(Ref<Shader> shader);
		Ref<Shader> Load(const std::string& filePath);
		Ref<Shader> Load(const std::string& name,const std::string& filePath);
		Ref<Shader> Get(const std::string& name);
		bool Exists(const std::string& name);

	private:
		std::unordered_map<std::string,Ref<Shader>> m_Shaders;
	};

}