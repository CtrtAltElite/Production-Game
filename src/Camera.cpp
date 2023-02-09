#include "Camera.h"

#include "Config.h"

Camera::Camera()
{
    SetWidth(Config::SCREEN_WIDTH);
    SetHeight(Config::SCREEN_HEIGHT);
}

Camera::~Camera()
=default;


glm::vec2 Camera::CameraDisplace(glm::vec2 position)
{
    if (IsEnabled())
        return glm::vec2{position.x-GetTransform()->position.x,position.y-GetTransform()->position.y};
    return position;
    
}


