#include "Shark.h"

#include "Camera.h"
#include "TextureManager.h"
#include "Util.h"
#include "WorldManager.h"

Shark::Shark()
{
	TextureManager::Instance().Load("../Assets/textures/Brute_Shark.png", "shark");
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
	TextureManager::Instance().Draw("shark", Camera::Instance().CameraDisplace(m_rigidBody->GetPosition()), m_angleToPlayer*Util::Rad2Deg, 255, true);
}

void Shark::Update()
{
	Move();
}

void Shark::Move()
{
	if (GetRigidBody()->GetTransform().p != GetDirection())
	{
		GetRigidBody()->ApplyForceToCenter({ GetDirection().x * m_speed,GetDirection().y * m_speed }, true);
	}
}

void Shark::LookTowardsPlayer(b2Vec2 player_position)
{
	b2Vec2 movement_arm = player_position - GetRigidBody()->GetTransform().p;
	ChangeDirection(movement_arm); // Sets the direction to the current mousePos

	b2Vec2 toTarget = { player_position.x - player_position.x, player_position.y - player_position.y };
	m_angleToPlayer = b2Atan2(toTarget.y, toTarget.x);

	float nextAngle = GetRigidBody()->GetAngle() + GetRigidBody()->GetAngularVelocity() / 10.0;
	float totalRotation = m_angleToPlayer - nextAngle;
	while (totalRotation < -180 * Util::Deg2Rad) totalRotation += 360 * Util::Deg2Rad;
	while (totalRotation > 180 * Util::Deg2Rad) totalRotation -= 360 * Util::Deg2Rad;
	float desiredAngularVelocity = totalRotation * 10;
	float change = 1 * Util::Deg2Rad; //allow 1 degree rotation per time step
	desiredAngularVelocity = std::min(change, std::max(-change, desiredAngularVelocity));
	float impulse = GetRigidBody()->GetInertia() * desiredAngularVelocity;
	GetRigidBody()->ApplyAngularImpulse(impulse * 10.0f, true);
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