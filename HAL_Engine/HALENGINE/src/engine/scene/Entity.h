#pragma once

#include "Transform.h"
#include <memory>
#include "engine/renderer/Shader.h"
#include "engine/renderer/VertexArray.h"

namespace Haleng {
	class Entity : public Transform
	{
	public:
		Entity();
		virtual ~Entity() = default;

		virtual glm::vec3& GetPosition() override { return m_Data.position; }
		virtual void const SetPosition(glm::vec3 position) override;

		virtual glm::vec3& GetRotation() override { return m_Data.eulerRotation; }
		virtual void const SetRotation(glm::vec3 rotation) override;

		virtual glm::vec3& GetScale() override { return m_Data.scale; }
		virtual void const SetScale(glm::vec3 scale) override;

		glm::mat4x4& GetTransform() { return m_Data.globalTransform; }

		inline Shader& GetShader() { return *m_Shader; }
		void SetShader(const std::string& vertexSrc, const std::string& fragmentSrc);

		std::shared_ptr<VertexArray> GetVertexArray() { return m_VertexArray; }

	private:
		void RecalculateTransform();
	private:
		Transform::Data m_Data;
		std::unique_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;
	private: //test stb image
		uint32_t m_TextureID = 0;
		int m_Width;
		int m_Height;
	};
}