#include "halpch.h"

#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace  Haleng 
{
	Camera::Camera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
	{
		RecalculateViewMatrix();
	}

	void Camera::RecalculateViewMatrix()
	{
		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f), m_Data.position) *
			glm::rotate(glm::mat4(1.0f), glm::radians((float)0.0), glm::vec3(0, 0, 1.0f));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	const void Camera::SetPosition(const glm::vec3& position)
	{
		m_Data.position = position;
		RecalculateViewMatrix();
	}

	const void Camera::SetScale(const glm::vec3& scale)
	{

	}
}