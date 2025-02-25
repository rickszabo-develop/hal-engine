#pragma once

#include "Transform.h"
#include <glm/glm.hpp>

namespace Haleng {
	class Camera : public Transform
	{
	public:
		Camera(float fovy, float aspect, float zNear, float zFar);

		virtual glm::vec3& GetPosition() override { return m_Data.position; }
		virtual void const SetPosition(glm::vec3 position) override;

		virtual glm::vec3& GetRotation() override { return m_Data.eulerRotation; }
		virtual void const SetRotation(glm::vec3 rotation) override;

		virtual glm::vec3& GetScale() override { return m_Data.scale; }
		virtual void const SetScale(glm::vec3 scale) override;

		const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }

	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		Transform::Data m_Data;
	};
}