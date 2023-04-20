#include "SeaUrchin.h"
#include "TextureManager.h"
#include "Camera.h"
#include "Game.h"
#include "Util.h"

SeaUrchin::SeaUrchin()
{
	textureName = "SeaUrchin";
	TextureManager::Instance().Load("../Assets/sprites/obstacles/images/sea_urchin.png", textureName);

	SetWidth(TextureManager::Instance().GetTextureSize(textureName).x);
	SetHeight(TextureManager::Instance().GetTextureSize(textureName).y);

	GetRigidBody()->mass = 1.0f;
	SetType(GameObjectType::SEA_URCHIN);
}

void SeaUrchin::Draw()
{
	if (Game::Instance().GetDebugMode())
	{
		Util::DrawRect(Camera::Instance().CameraDisplace(this) -
			glm::vec2(this->GetWidth() * 0.5f, this->GetHeight() * 0.5f),
			this->GetWidth(), this->GetHeight());
	}

	TextureManager::Instance().Draw(textureName, Camera::Instance().CameraDisplace(this), 
		GetTransform()->rotation.r * Util::Rad2Deg, 255, true, SDL_FLIP_NONE);
}

void SeaUrchin::Update()
{
	GetTransform()->position.x = Util::Clamp(GetTransform()->position.x, Game::Instance().GetLevelBoundaries().x, Game::Instance().GetLevelBoundaries().y);
	GetTransform()->position.y = Util::Clamp(GetTransform()->position.y, Game::Instance().GetLevelBoundaries().z, Game::Instance().GetLevelBoundaries().w);

	if (GetTransform()->position.x >= Game::Instance().GetLevelBoundaries().x)
	{
		randomDecreasingNumber = rand() % 4;
	}
	else if (GetTransform()->position.x <= Game::Instance().GetLevelBoundaries().y)
	{
		randomDecreasingNumber = -(rand() % 4);
	}
	if (GetTransform()->position.y >= Game::Instance().GetLevelBoundaries().z)
	{
		randomDecreasingNumber = -(rand() % 4);
	}
	else if (GetTransform()->position.y <= Game::Instance().GetLevelBoundaries().w)
	{
		randomDecreasingNumber = rand() % 4;
	}

	GetTransform()->position.x += randomDecreasingNumber;
	GetTransform()->position.y += randomDecreasingNumber;
}

void SeaUrchin::Clean()
{
	Obstacle::Clean();
}
