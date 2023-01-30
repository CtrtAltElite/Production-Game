#include <Camera.h>

b2Vec2 Camera::CameraDisplace(b2Vec2 position)
{
	return b2Vec2{ position.x - m_position.x + m_size.x / 2,position.y - m_position.y + m_size.y / 2 };
	return position;
}

//glm::ivec2 Camera::CameraDisplace(glm::ivec2 position)
//{
//	return glm::ivec2{ position.x - m_position.x +m_size.x/2,position.y - m_position.y+m_size.y/2};
//	return position;
//}
