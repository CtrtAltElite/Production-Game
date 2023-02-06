#pragma once
#include <glm/detail/type_vec.hpp>

#include "Transform.h"

class Camera
{
public:
	static Camera& Instance()
	{
		static Camera instance;
		return instance;
	}
	Transform* GetTransform(){return &m_transform;}
	glm::vec2 CameraDisplace(glm::vec2 position);
private:
	Transform m_transform;
};
