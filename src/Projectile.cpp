#include "Projectile.h"

#include "Camera.h"
#include "Game.h"
#include "TextureManager.h"
#include "WorldManager.h"

Projectile::Projectile(Player* player)
{
	TextureManager::Instance().Load("../Assets/textures/Circle.png", "projectile");

	const auto size = TextureManager::Instance().GetTextureSize("projectile");
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));
	m_mousepos = Game::Instance().GetMousePosition();
	isColliding = false;
	m_player = player;
	m_angle = (atan2((m_player->GetRigidBody()->GetPosition().y - m_mousepos.y) - Camera::Instance().GetPosition().y, (m_player->GetRigidBody()->GetPosition().x - m_mousepos.x) - Camera::Instance().GetPosition().x));
	m_vector = { -cos(m_angle) * 50,-sin(m_angle) * 50 };
	Start();
	
	

	SetType(GameObjectType::PROJECTILE);
	
}


void Projectile::Draw()
{
	// draw the target
	b2Vec2 position = GetRigidBody()->GetPosition();
	position.x -= Camera::Instance().GetPosition().x;
	position.y -= Camera::Instance().GetPosition().y;
	TextureManager::Instance().Draw("projectile", position, 0, 180, true);
}
void Projectile::Start()
{
	InitRigidBody();
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(GetWidth()/2, GetHeight()/2);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 0.1f;
	fixtureDef.friction = 0.1f;
	GetRigidBody()->CreateFixture(&fixtureDef);
	
	std::cout << m_rigidBody->GetPosition().x << std::endl << m_rigidBody->GetPosition().y << std::endl;
	GetRigidBody()->ApplyForceToCenter({ m_vector.x * 100000,m_vector.y * 100000 }, true);
	m_player->GetRigidBody()->ApplyForceToCenter({ -m_vector.x * 20000.0f, -m_vector.y * 20000.0f }, true);
}

void Projectile::Update()
{
	
	
}
void Projectile::Clean()
{
	
}

void Projectile::InitRigidBody()
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(m_player->GetRigidBody()->GetPosition().x + m_vector.x, m_player->GetRigidBody()->GetPosition().y + m_vector.y);
	bodyDef.enabled = true;
	bodyDef.bullet = true;
	bodyDef.type = b2_dynamicBody;
	m_rigidBody = WorldManager::Instance().GetWorld()->CreateBody(&bodyDef);
}
b2Body* Projectile::GetRigidBody()
{
	return m_rigidBody;
}
