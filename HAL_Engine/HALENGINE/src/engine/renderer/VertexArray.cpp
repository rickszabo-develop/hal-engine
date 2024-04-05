#include "halpch.h"
#include "engine/Core.h"

#include "Renderer.h"
#include "engine/renderer/VertexArray.h"
#include "platform/opengl/OpenGLVertexArray.h"

namespace Haleng
{
	VertexArray::~VertexArray()
	{
	}

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI()) 
		{
		case RendererAPI::API::None:		HALENG_ASSERT(false, "RendererAPI None, not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return new OpenGLVertexArray();
		}

		HALENG_ASSERT(false, "Unknown renderer API");
		return nullptr;
	}
}