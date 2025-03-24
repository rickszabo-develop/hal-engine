#pragma once

#include "engine/renderer/RendererAPI.h"
#include "engine/renderer/RenderCommand.h"

namespace Haleng 
{
	class Renderer {
	public:
		static void Init();
		static void BeginScene(class Camera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<class Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetApi(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static std::unique_ptr<SceneData> s_SceneData;
	};
}