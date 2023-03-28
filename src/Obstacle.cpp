#include "Obstacle.h"


#include "Camera.h"
#include "EventManager.h"
#include "Game.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "Util.h"

Obstacle::Obstacle()
{
	TextureManager::Instance().Load("../Assets/textures/obstacle.png", "obstacle");

	const auto size = TextureManager::Instance().GetTextureSize("obstacle");
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));

	GetTransform()->position = glm::vec2(300.0f, 300.0f);
	GetRigidBody()->bounds = glm::vec2(GetWidth(), GetHeight());
	GetRigidBody()->mass = 0.0f; // infinite mass essentially.

	SetIsCentered(true);
	SetType(GameObjectType::OBSTACLE);
	GetRigidBody()->isColliding = false;
	m_deleteMe = false;

	SoundManager::Instance().Load("../Assets/audio/yay.ogg", "yay", SoundType::SOUND_SFX);

	tag = "obstacle";
}

Obstacle::Obstacle(const char* fileName, const char* texture)
{
	TextureManager::Instance().Load(texture, fileName);

	textureName = fileName;

	const auto size = TextureManager::Instance().GetTextureSize(fileName);
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));

	GetTransform()->position = glm::vec2(300.0f, 300.0f);
	GetRigidBody()->bounds = glm::vec2(GetWidth(), GetHeight());
	GetRigidBody()->mass = 0.0f; // infinite mass essentially.

	SetIsCentered(true);
	SetType(GameObjectType::OBSTACLE);
	GetRigidBody()->isColliding = false;
	m_deleteMe = false;

	SoundManager::Instance().Load("../Assets/audio/yay.ogg", "yay", SoundType::SOUND_SFX);
}


Obstacle::~Obstacle()
= default;

void Obstacle::Draw()
{
	if(Game::Instance().GetDebugMode())
	{
		Util::DrawRect(Camera::Instance().CameraDisplace(this) -
			glm::vec2(this->GetWidth() * 0.5f, this->GetHeight() * 0.5f),
			this->GetWidth(), this->GetHeight());
		
	}
	TextureManager::Instance().Draw(textureName, Camera::Instance().CameraDisplace(this), 0, 100, true);
}

void Obstacle::Update()
{
	if (m_isPlacing) { // If we are currently placing the obstacle
		GetTransform()->position = Util::GetMousePos() + Camera::Instance().GetTransform()->position;

		if (EventManager::Instance().MousePressed(1)) // If we left-click, place the object.
		{
			m_isPlacing = false;
		}
	}
}

void Obstacle::Clean()
{
}

bool Obstacle::GetDeleteMe() const
{
	return m_deleteMe;
}

void Obstacle::SetDeleteMe(bool deleteMe)
{
	m_deleteMe = deleteMe;
}

ObstaclePool::ObstaclePool()
{

}

void ObstaclePool::Update()
{
	for (unsigned i = 0; i < m_obstacles.size(); i++)
	{
		if (m_obstacles[i]->GetDeleteMe() == true)
		{
			delete m_obstacles[i];
			m_obstacles[i] = nullptr;
			m_obstacles.erase(i + m_obstacles.begin());
			m_obstacles.shrink_to_fit();
		} else
		{
			m_obstacles[i]->Update();
		}
	}
}

void ObstaclePool::Clean()
{
}

void ObstaclePool::Draw()
{
	for (auto obstacle : m_obstacles)
	{
		obstacle->Draw();
	}
}

std::vector<Obstacle*> ObstaclePool::GetPool()
{
	return m_obstacles;
}

void ObstaclePool::Spawn(Obstacle* obstacleType)
{
	m_obstacles.push_back(obstacleType);
}
