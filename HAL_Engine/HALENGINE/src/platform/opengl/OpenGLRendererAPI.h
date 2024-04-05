#pragma once

#include <glm/glm.hpp>
#include "engine/renderer/RendererAPI.h"

namespace Haleng
{
	class OpenGLRendererAPI : public RendererAPI 
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexes(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}