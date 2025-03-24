#pragma once
#include <memory>
#include "VertexArray.h"
#include "RendererAPI.h"

namespace Haleng
{
	class RenderCommand 
	{
	public:
		inline static void Init()
		{
			s_RendererAPI->Init();
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear() 
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexes(const std::shared_ptr<VertexArray>& vertexArray) 
		{
			s_RendererAPI->DrawIndexes(vertexArray);
		}

	private: 
		static RendererAPI* s_RendererAPI;
	};
}