#pragma once

#include <glm/glm.hpp>
#include "engine/scene/Transform3D.h"

namespace Haleng
{
	class Camera : public Transform3D
	{
	public:
		Camera(float left, float right, float bottom, float top);

		virtual glm::vec3& GetPosition() override { return m_Data.position; }
		virtual const void SetPosition(const glm::vec3& position) override;

		/*float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }*/

		virtual glm::vec3& GetScale() override { return m_Data.scale; }
		virtual const void SetScale(const glm::vec3& scale) override;

		const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		Transform3D::Data m_Data;
	};
}