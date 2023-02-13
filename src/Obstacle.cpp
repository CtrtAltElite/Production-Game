#include "Obstacle.h"


#include "Camera.h"
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

	SetType(GameObjectType::OBSTACLE);
	GetRigidBody()->isColliding = false;

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
	TextureManager::Instance().Draw("obstacle", Camera::Instance().CameraDisplace(this), 0, 100, true);
}

void Obstacle::Update()
{
}

void Obstacle::Clean()
{
}
