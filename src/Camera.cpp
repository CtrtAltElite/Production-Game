#include "Camera.h"


glm::vec2 Camera::CameraDisplace(glm::vec2 position)
{
    return glm::vec2{position.x-m_transform.position.x,position.y-m_transform.position.y};
}

