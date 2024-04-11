#pragma once

#include <glm/glm.hpp>

namespace Haleng
{
	class Transform3D
	{
	public:
		struct Data
		{
			glm::mat4 globalTransform;
			glm::mat4 localTransform;

			glm::vec3 position;
			glm::vec3 eulerRotation = glm::vec3(0, 0, 0);
			glm::vec3 scale;

			bool visible = true;
		};

	public:
		Transform3D(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
		~Transform3D();

		inline glm::vec3 GetPosition() { return m_Data.position; }
		void const SetPosition(const glm::vec3& translation);

		inline glm::vec3 GetRotation() { return m_Data.eulerRotation; }
		void const SetRotation(const glm::vec3& rotation);

		inline glm::vec3 GetScale() { return m_Data.scale; }
		void const SetScale(const glm::vec3& scale);

		void const UpdateTransforms();
	private:
		Data m_Data;
	};
}