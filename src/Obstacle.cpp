#include "Obstacle.h"


#include "Game.h"
#include "SoundManager.h"
#include "TextureManager.h"

Obstacle::Obstacle()
{
	TextureManager::Instance().Load("../Assets/textures/obstacle.png", "obstacle");

	const auto size = TextureManager::Instance().GetTextureSize("obstacle");
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));
	b2Vec2 position = { 300.0f,300.0f };
	InitRigidBody(position);

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
void Obstacle::InitRigidBody(b2Vec2 position)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x, position.y);
	m_rigidBody = Game::Instance().world->CreateBody(&bodyDef);
}
b2Body* Obstacle::GetRigidBody()
{
	return m_rigidBody;
}
