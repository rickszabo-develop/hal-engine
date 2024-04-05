#pragma once

#include "engine/renderer/RendererAPI.h"
#include "engine/renderer/RenderCommand.h"

namespace Haleng 
{
	class Renderer {
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetApi(); }
	};
}