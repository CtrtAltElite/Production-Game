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

Obstacle::Obstacle(const char* fileName, const char* texture, int scale)
{
	m_scale = scale;
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

Obstacle::Obstacle(const char* fileName, const char* texture, const char* txtName)
{
	TextureManager::Instance().LoadSpriteSheet(txtName, texture, fileName);

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
	m_isSpriteSheet = true;
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
	if (!m_isSpriteSheet)
	{
		TextureManager::Instance().DrawScale(textureName, Camera::Instance().CameraDisplace(this).x, Camera::Instance().CameraDisplace(this).y, m_scale, 0, 255, true);
	}
}

void Obstacle::Update()
{
	
}

void Obstacle::Clean()
{
}

void Obstacle::UpdatePlacement()
{
	if (m_isPlacing) { // If we are currently placing the obstacle
		GetTransform()->position = EventManager::Instance().GetMousePosition() + Camera::Instance().GetTransform()->position;

		std::cout << "placing" << std::endl;
		if (EventManager::Instance().MousePressed(1)) // If we left-click, place the object.
		{
			std::cout << "placed" << std::endl;
			m_isPlacing = false;
			GetTransform()->position = Util::GetMousePos() + Camera::Instance().GetTransform()->position;
		}
	}
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
			// ONLY update if we are not level editing.
			if (!Game::Instance().GetLevelEditorMode()) {
				m_obstacles[i]->Update();
			}
			m_obstacles[i]->UpdatePlacement();
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
