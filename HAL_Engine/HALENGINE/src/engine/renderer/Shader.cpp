#include "halpch.h"
#include "engine/Core.h"
#include "Shader.h"
#include "Renderer.h"
#include "platform/opengl/OpenGLShader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Haleng {
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	HALENG_ASSERT(false, " None, not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		HALENG_ASSERT(false, "Unknown renderer API");
		return nullptr;
	}
}