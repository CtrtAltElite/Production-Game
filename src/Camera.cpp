#include "Camera.h"


glm::vec2 Camera::CameraDisplace(glm::vec2 position)
{
    if (m_isEnabled)
        return glm::vec2{position.x-m_transform.position.x,position.y-m_transform.position.y};
    return position;
    
}

void Camera::SetEnabled(bool enabled)
{
    m_isEnabled = enabled;
}

bool Camera::GetEnabled()
{
    return m_isEnabled;
}

