#pragma once

#include "glm/glm.hpp"

namespace Haleng {
	class Transform
	{
	public:
		struct Data {
			glm::mat4x4 globalTransform = glm::mat4x4(1.f);
			glm::vec3 position = glm::vec3(0.f, 0.f, 0.f);
			glm::vec3 eulerRotation = glm::vec3(0.f, 0.f, 0.f);
			glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f);
		};

	private:
		virtual glm::vec3& GetPosition() = 0;
		virtual void const SetPosition(glm::vec3 position) = 0;

		virtual glm::vec3& GetRotation() = 0;
		virtual void const SetRotation(glm::vec3 rotation) = 0;

		virtual glm::vec3& GetScale() = 0;
		virtual void const SetScale(glm::vec3 scale) = 0;

	};
}