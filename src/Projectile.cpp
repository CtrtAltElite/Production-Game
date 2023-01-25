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
	dynamicBox.SetAsBox(GetWidth()/3, GetHeight()/3);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 0.5f;
	fixtureDef.friction = 1.0f;
	GetRigidBody()->CreateFixture(&fixtureDef);
	
	std::cout << m_rigidBody->GetPosition().x << std::endl << m_rigidBody->GetPosition().y << std::endl;
	GetRigidBody()->ApplyForceToCenter({ m_vector.x * 15000,m_vector.y * 15000 }, true);
}

void Projectile::Update()
{
	
	
}
void Projectile::Clean()
{
	
}

void Projectile::InitRigidBody()
{
	m_rigidBody = WorldManager::Instance().CreateBulletRigidBody({ m_player->GetRigidBody()->GetPosition().x+m_vector.x,m_player->GetRigidBody()->GetPosition().y+m_vector.y});
}
b2Body* Projectile::GetRigidBody()
{
	return m_rigidBody;
}
