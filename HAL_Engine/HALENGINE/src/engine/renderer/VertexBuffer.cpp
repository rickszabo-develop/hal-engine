#include "halpch.h"
#include "engine/Core.h"

#include "Renderer.h"
#include "engine/renderer/VertexBuffer.h"
#include "platform/opengl/OpenGLVertexBuffer.h"


namespace Haleng
{
	VertexBuffer::~VertexBuffer()
	{
	}

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:		HALENG_ASSERT(false, "RendererAPI None, not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return new OpenGLVertexBuffer(vertices, size);
		}

		HALENG_ASSERT(false, "Unknown renderer API");
		return nullptr;
	}
}