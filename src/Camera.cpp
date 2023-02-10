#include "Camera.h"

#include "Config.h"

Camera::Camera()
{
    SetWidth(Config::SCREEN_WIDTH);
    SetHeight(Config::SCREEN_HEIGHT);
}

Camera::~Camera()
=default;


glm::vec2 Camera::CameraDisplace(DisplayObject* object)
{
    if (IsEnabled())
    {
        glm::vec2 displace = {object->GetTransform()->position.x-GetTransform()->position.x,object->GetTransform()->position.y-GetTransform()->position.y};
        return displace;
    }
    return object->GetTransform()->position;
}



