#pragma once
#include "Hazel/Renderer/Texture.h"

namespace Hazel
{
	class OpenGLTexture : public Texture2D
	{
	public:
		OpenGLTexture(const std::string& path);
		virtual ~OpenGLTexture();

		virtual uint32_t GetWidth()const override;
		virtual uint32_t GetHeight()const override;
		virtual void Bind(uint32_t slot = 0)const override;
	private:
		std::string m_path;
		uint32_t m_Width;
		uint32_t m_Height; 

		uint32_t m_RendererID;
	};

}