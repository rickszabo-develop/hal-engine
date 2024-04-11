#include "halpch.h"
#include "Transform3D.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Haleng
{
	Transform3D::Transform3D(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
	{
		SetPosition(position);
		SetRotation(rotation);
		SetScale(scale);
	}

	Transform3D::~Transform3D()
	{
	}

	void const Transform3D::SetPosition(const glm::vec3& translation)
	{
		m_Data.position = translation;
		glm::translate(m_Data.globalTransform, translation);
	}
	void const Transform3D::SetRotation(const glm::vec3& rotation)
	{
		m_Data.eulerRotation = rotation;
		//glm::rotate(m_Data.globalTransform, rotation);
	}

	void const Transform3D::SetScale(const glm::vec3& scale)
	{
		m_Data.scale = scale;
		glm::scale(m_Data.globalTransform, scale);
	}
	void const Transform3D::UpdateTransforms()
	{
		SetPosition(m_Data.position);
		SetRotation(m_Data.eulerRotation);
		SetScale(m_Data.scale);
	}
}
