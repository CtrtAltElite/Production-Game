#pragma once
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
private:
	b2Vec2 m_position={1280/2,720/2};
	b2Vec2 m_size{1280,720};
};
