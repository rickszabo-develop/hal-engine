#include "halpch.h"

#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>


namespace  Haleng 
{
	Camera::Camera(float fovy, float aspect, float zNear, float zFar)
		//: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
		:m_ProjectionMatrix(glm::perspective(fovy, aspect, zNear, zFar))
	{
		RecalculateViewMatrix();
	}

	void Camera::RecalculateViewMatrix()
	{
		m_Data.globalTransform = glm::translate(glm::mat4(1), m_Data.position) *
			glm::rotate(glm::mat4(1), glm::radians(m_Data.eulerRotation.z), glm::vec3(0, 0, 1.0f)) *
			glm::scale(glm::mat4(1), m_Data.scale);

		m_ViewMatrix = glm::inverse(m_Data.globalTransform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	const void Camera::SetPosition(const glm::vec3& position)
	{
		m_Data.position = position;
		RecalculateViewMatrix();
	}

	const void Camera::SetScale(const glm::vec3& scale)
	{
		m_Data.scale = scale;
		RecalculateViewMatrix();
	}
	const void Camera::SetRotation(const glm::vec3& rotation)
	{
		m_Data.eulerRotation = rotation;
		RecalculateViewMatrix();
	}
}