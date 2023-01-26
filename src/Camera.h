#pragma once
#include <glm/vec2.hpp>

#include "box2d.h"
class Camera
{
public:
	static Camera& Instance()
	{
		static Camera instance;
		return instance;
	}
	b2Vec2 GetPosition() { return m_position; }
	b2Vec2 GetSize() { return m_size; }
	void SetPosition(b2Vec2 pos) { m_position = pos; }
	void SetSize(b2Vec2 size) { m_size = size; }
	b2Vec2 CameraDisplace(b2Vec2 position);
	glm::ivec2 CameraDisplace(glm::ivec2 position);
private:
	b2Vec2 m_size{1280,720};
	b2Vec2 m_position = { m_size.x/2,m_size.y/2 };

};
