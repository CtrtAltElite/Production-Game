#include "Obstacle.h"


#include "Game.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "WorldManager.h"

Obstacle::Obstacle()
{
	TextureManager::Instance().Load("../Assets/textures/obstacle.png", "obstacle");

	const auto size = TextureManager::Instance().GetTextureSize("obstacle");
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));
	b2Vec2 position = { 300.0f,300.0f };
	InitRigidBody();

	SetType(GameObjectType::OBSTACLE);
	isColliding = false;

	SoundManager::Instance().Load("../Assets/audio/yay.ogg", "yay", SoundType::SOUND_SFX);
}

Obstacle::~Obstacle()
= default;

void Obstacle::Draw()
{
	TextureManager::Instance().Draw("obstacle", GetRigidBody()->GetPosition(), 0, 255, true);
}

void Obstacle::Update()
{
}

void Obstacle::Clean()
{
}
void Obstacle::InitRigidBody()
{
	m_rigidBody = WorldManager::Instance().CreateRigidBody({ 400.0f,400.0f });
}
b2Body* Obstacle::GetRigidBody()
{
	return m_rigidBody;
}
