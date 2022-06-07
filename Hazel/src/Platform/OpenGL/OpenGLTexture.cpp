#include "hzpch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"
#include <glad/glad.h>

namespace Hazel
{

	OpenGLTexture::OpenGLTexture(const std::string& path) : m_path(path)
	{
		int width,height,channel;
		stbi_set_flip_vertically_on_load(1);
		//����image ��������Ϊ ·�������ߣ���ʽRGB����Ҫת���ĸ�ʽ ����Ҫת�� Ϊ0 
		stbi_uc* data = 	stbi_load(path.c_str(),&width,&height,&channel,0);
		HZ_CORE_ASSERT(data,"Faile To Load Image !");
		m_Width = width;
		m_Height = height;

		GLenum interFormat=0, Format = 0;
		if (channel == 3)
		{
			interFormat = GL_RGB8;
			Format = GL_RGB;
		}
		else
		{
			interFormat = GL_RGBA8;
			Format = GL_RGBA;	
		}

		//����
		glCreateTextures(GL_TEXTURE_2D,1,&m_RendererID);
		//�����ڴ�  // �������� ID�� MipMap(LOD), ��ʽ��OpenGL��ʽ��
		glTextureStorage2D(m_RendererID,1,interFormat,m_Width,m_Height);
		// Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
		/*glTexParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);*/
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//���������������� (��ʱFormatΪͼƬ��)
		glTextureSubImage2D(m_RendererID,0,0,0,m_Width,m_Height,Format,GL_UNSIGNED_BYTE,data);
		
		stbi_image_free(data);
	}

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1,&m_RendererID);
	}

	uint32_t OpenGLTexture::GetWidth() const
	{
		return m_Width;
	}

	uint32_t OpenGLTexture::GetHeight() const
	{
		return m_Height;
	}

	void OpenGLTexture::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot,m_RendererID);
	}

}