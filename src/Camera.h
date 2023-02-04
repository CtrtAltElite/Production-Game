#pragma once
class Camera
{
public:
	static Camera& Instance()
	{
		static Camera instance;
		return instance;
	}
	glm::vec2 GetPosition() { return m_position; }
	glm::vec2 GetSize() { return m_size; }
	void SetPosition(glm::vec2 pos) { m_position = pos; }
	void SetSize(glm::vec2 size) { m_size = size; }
private:
	glm::vec2 m_position={1280/2,720/2};
	glm::vec2 m_size{1280,720};
};
