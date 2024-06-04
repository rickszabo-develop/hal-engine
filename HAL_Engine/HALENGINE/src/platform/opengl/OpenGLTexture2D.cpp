#include "halpch.h"
#include "OpenGLTexture2D.h"
#include <stb_image.h>

namespace Haleng
{
	void OpenGLTexture2D::Bind() const
	{
	}
	Texture2D* OpenGLTexture2D::Create(const std::string& path)
	{
		stbi_set_flip_vertically_on_load(true);
		//stbi_load(path.c_str(), (int*)&m_Width, (int*)&m_Height, (int*)&m_NrChannels, 0);*/
		return nullptr;
	}
}
