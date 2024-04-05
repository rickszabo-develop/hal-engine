#include "halpch.h"
#include "engine/Core.h"
#include "engine/Log.h"

#include "engine/renderer/IndexBuffer.h"
#include "engine/renderer/Renderer.h"
#include "platform/opengl/OpenGLIndexBuffer.h"
namespace Haleng 
{
	IndexBuffer::~IndexBuffer()
	{
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:		HALENG_ASSERT(false, "RendererAPI None, not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return new OpenGLIndexBuffer(indices, count);
		}

		HALENG_ASSERT(false, "Unknown renderer API");
		return nullptr;
	}
}	
