#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>

namespace Haleng
{
	class Transform3D
	{
	public:
		struct Data
		{
			glm::mat4x4 globalTransform = glm::mat4x4(1);

			glm::vec3 position = glm::vec3(0, 0, 0);
			glm::vec3 eulerRotation = glm::vec3(0, 0, 0);
			glm::vec3 scale = glm::vec3(1, 1, 1);

			bool visible = true;
		};

	public:
		virtual glm::vec3& GetPosition() = 0;
		virtual const void SetPosition(const glm::vec3& position) = 0;

		virtual const glm::vec3& GetRotation() = 0;
		virtual void const SetRotation(const glm::vec3& rotation) = 0;

		virtual glm::vec3& GetScale() = 0;
		virtual const void SetScale(const glm::vec3& scale) = 0;
	};
}