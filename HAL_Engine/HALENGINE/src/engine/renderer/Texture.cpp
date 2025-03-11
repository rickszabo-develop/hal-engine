#include "halpch.h"
#include "Texture.h"
#include "engine/Log.h"
#include "Renderer.h"
#include "platform/opengl/OpenGLTexture2D.h"

namespace Haleng {
	Texture2D* Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	HALENG_ASSERT(false, " None, not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return new OpenGLTexture2D(path);
		}

		HALENG_ASSERT(false, "Unknown renderer API");
		return nullptr;
	}
}
