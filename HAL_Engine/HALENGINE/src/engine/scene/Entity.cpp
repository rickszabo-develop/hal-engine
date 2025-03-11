#include "halpch.h"
#include "Entity.h"
#include "engine/Log.h"
#include "engine/renderer/Texture.h"
#include <glm/ext/matrix_transform.hpp>

namespace Haleng {
	Entity::Entity()
	{
		m_VertexArray.reset(VertexArray::Create());

		float vertices[4 * 7] = {
			-0.5f, -0.5f, 0.0f, 2.0f, 2.0f,
			0.5f, -0.5f, 0.0f,	0.0f, 2.0f,
			0.5f, 0.5f, 0.0f,	0.0f, 0.0f,
			-0.5f, 0.5f, 0.0f,	2.0f, 0.0f,
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" },
		};
		
		vertexBuffer->SetLayout(layout);

		uint32_t indices[6] = { 
			0, 1, 2,
			0, 2, 3
		};

		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);
		
		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = vec4(a_TexCoord.x, a_TexCoord.y, 0.0, 0.0);
				gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Color;

			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_Color.xy);
			}
		)";
		//--
		SetShader(vertexSrc, fragmentSrc);
		RecalculateTransform();

		Texture2D* ss1 = Texture2D::Create("1956757892137-screenshoturl_2.jpg");
		ss1->Bind(0);
		m_Shader->SetUniform1i("u_Texture", 0);
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