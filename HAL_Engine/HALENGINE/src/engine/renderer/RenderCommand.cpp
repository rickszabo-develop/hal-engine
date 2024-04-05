#include "halpch.h"
#include "RenderCommand.h"

#include "platform/opengl/OpenGLRendererAPI.h"

namespace Haleng
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}
