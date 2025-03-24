#include "halpch.h"

#include "engine/renderer/Renderer.h"
#include "engine/renderer/RenderCommand.h"
#include "engine/renderer/Shader.h"
#include "engine/scene/Camera.h"

namespace Haleng 
{
	std::unique_ptr<Renderer::SceneData> Renderer::s_SceneData = std::make_unique<Renderer::SceneData>();

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::BeginScene(Camera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->SetUniformMat4f("u_ViewProjectionMatrix", s_SceneData->ViewProjectionMatrix);
		shader->SetUniformMat4f("u_Transform", transform);
		shader->Bind();
		vertexArray->Bind();
		RenderCommand::DrawIndexes(vertexArray);
	}
}