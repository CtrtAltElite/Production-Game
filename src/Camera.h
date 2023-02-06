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
	void Update();
	glm::vec2 CameraDisplace(glm::vec2 position);
private:
	Transform m_transform;
};
