#include "halpch.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Haleng {
    Camera::Camera(float fovy, float aspect, float zNear, float zFar)
        :m_ProjectionMatrix(glm::perspective(fovy, aspect, zNear, zFar))
    {
        RecalculateViewMatrix();
    }

    void Camera::RecalculateViewMatrix()
    {
        m_Data.globalTransform = 
            glm::translate(glm::mat4(1.0f), -m_Data.position) *
            glm::rotate(glm::mat4(1.0f), glm::radians(m_Data.eulerRotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(m_Data.eulerRotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(m_Data.eulerRotation.z), glm::vec3(0.0f, 0.0f, 1.0f)) *
            glm::scale(glm::mat4(1.0f), m_Data.scale);

        m_ViewMatrix = glm::inverse(m_Data.globalTransform);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void const Camera::SetPosition(glm::vec3 position)
    {
        m_Data.position = position;
        RecalculateViewMatrix();
    }

    void const Camera::SetRotation(glm::vec3 rotation)
    {
        m_Data.eulerRotation = rotation;
        RecalculateViewMatrix();
    }

    void const Camera::SetScale(glm::vec3 scale)
    {
        m_Data.scale = scale;
        RecalculateViewMatrix();
    }
}
