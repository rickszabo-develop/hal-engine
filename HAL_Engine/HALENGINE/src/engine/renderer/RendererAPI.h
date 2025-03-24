#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "engine/renderer/VertexArray.h"

namespace Haleng 
{
	class RendererAPI 
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};

		virtual void Init() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexes(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		inline static API GetApi() { return s_API; }
	private:
		static API s_API;
	};
}