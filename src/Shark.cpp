#include "Shark.h"

#include "Camera.h"
#include "TextureManager.h"
#include "Util.h"
#include "WorldManager.h"

Shark::Shark()
{
	InitRigidBody();
	SetWidth(53); // Setting width of frame
	SetHeight(58); // Setting height of frame
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(GetWidth() / 3, GetHeight() / 3);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.5f;
	GetRigidBody()->CreateFixture(&fixtureDef);
	isColliding = false;
	SetType(GameObjectType::SHARK);
}

void Shark::Draw()
{
	TextureManager::Instance().Draw("player", Camera::Instance().CameraDisplace(m_rigidBody->GetPosition()), GetRigidBody()->GetAngle() * Util::Rad2Deg, 255, true);
}

void Shark::Update()
{
	Move();
}

void Shark::Move()
{
	
}

void Shark::LookTowardsPlayer(b2Vec2 player_position)
{
	
}


void Shark::Clean()
{
}

void Shark::TakeDamage(float damage)
{
	m_health -= damage;
	Util::Clamp(m_health, 0.0f, m_maxHealth);
	if (m_health == 0.0f)
		Die();
	
}

void Shark::Die()
{
	isDead = true;
}

void Shark::InitRigidBody()
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(200.0f, 200.0f);
	bodyDef.angle = 0;
	bodyDef.type = b2_dynamicBody;
	bodyDef.linearDamping = 0.8f;
	bodyDef.angularDamping = 1.0f;
	bodyDef.enabled = true;
	m_rigidBody = WorldManager::Instance().GetWorld()->CreateBody(&bodyDef);
}

b2Body* Shark::GetRigidBody()
{
	return m_rigidBody;
}

void Shark::ChangeDirection(float heading)
{
	const float x = (heading);
	const float y = (heading);
	m_currentDirection = b2Vec2(x, y);
}

void Shark::ChangeDirection(b2Vec2 direction)
{
	m_currentDirection = direction;
}

b2Vec2 Shark::GetDirection()
{
	return m_currentDirection;
}