#pragma once
#include <glm/detail/type_vec.hpp>

#include "Player.h"

class Camera : public GameObject
{
public:
	static Camera& Instance()
	{
		static Camera instance;
		return instance;
	}
	
	virtual ~Camera();
	
	void Draw() override{}
	void Clean() override{}
	void Update() override{}
	glm::vec2 CameraDisplace(glm::vec2 position);
private:
	Camera();
};
