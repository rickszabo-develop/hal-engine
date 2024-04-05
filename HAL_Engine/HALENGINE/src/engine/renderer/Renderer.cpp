#include "halpch.h"

#include "engine/renderer/Renderer.h"
#include "engine/renderer/RenderCommand.h"

namespace Haleng 
{
	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexes(vertexArray);
	}
}