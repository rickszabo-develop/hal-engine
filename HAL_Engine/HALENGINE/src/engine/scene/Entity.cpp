#include "halpch.h"
#include "Entity.h"
#include <glm/ext/matrix_transform.hpp>

namespace Haleng {
	Entity::Entity()
	{
		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f,	1.0f, 1.0f, 0.0f, 1.0f
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
		};

		vertexBuffer->SetLayout(layout);

		uint32_t indices[3] = { 0, 1, 2 };

		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);
		//--
		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";
		//--
		SetShader(vertexSrc, fragmentSrc);
		RecalculateTransform();
	}

	void const Entity::SetPosition(glm::vec3 position)
	{
		m_Data.position = position;
		RecalculateTransform();
	}

	void const Entity::SetRotation(glm::vec3 rotation)
	{
		m_Data.eulerRotation = rotation;
		RecalculateTransform();
	}

	void const Entity::SetScale(glm::vec3 scale)
	{
		m_Data.scale = scale;
		RecalculateTransform();
	}

	void Entity::SetShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		m_Shader.reset(Shader::Create(vertexSrc, fragmentSrc));
		m_Shader->Bind();

		RecalculateTransform();
	}

	void Entity::RecalculateTransform()
	{
		m_Data.globalTransform =
			glm::translate(glm::mat4(1.0f), m_Data.position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Data.eulerRotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Data.eulerRotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Data.eulerRotation.z), glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(glm::mat4(1.0f), m_Data.scale);
	}
}