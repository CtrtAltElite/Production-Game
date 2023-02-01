#include "Projectile.h"

#include "Camera.h"
#include "Game.h"
#include "TextureManager.h"
#include "Util.h"
#include "WorldManager.h"

Projectile::Projectile(Player* player)
{
	TextureManager::Instance().Load("../Assets/textures/Small_Torpedo.png", "projectile");

	const auto size = TextureManager::Instance().GetTextureSize("projectile");
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));
	isColliding = false;
	m_player = player;
	m_angle = player->GetRigidBody()->GetAngle();
	m_speed = 150;
	m_vector = { cos(m_angle) * m_speed,sin(m_angle) * m_speed };
	Start();
	
	

	SetType(GameObjectType::PROJECTILE);
	
}


void Projectile::Draw()
{
	// draw the target
	TextureManager::Instance().Draw("projectile", Camera::Instance().CameraDisplace(m_rigidBody->GetPosition()),m_angle*Util::Rad2Deg, 255, true);
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
	b2Vec2 pos = GetRigidBody()->GetPosition();
	if (pos.x<-deleteBuffer || pos.x>Game::Instance().GetWindowWidth() + deleteBuffer || pos.y<-deleteBuffer || pos.y>Game::Instance().GetWindowHeight() + deleteBuffer)
	{
		m_deleteMe = true;
		//std::cout << "Projectile set to delete" << std::endl;
	}
	
}
void Projectile::Clean()
{
}

void Projectile::InitRigidBody()
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(m_player->GetRigidBody()->GetPosition().x + m_vector.x*0.5, m_player->GetRigidBody()->GetPosition().y + m_vector.y*0.5);
	bodyDef.enabled = true;
	bodyDef.bullet = true;
	bodyDef.type = b2_dynamicBody;
	m_rigidBody = WorldManager::Instance().GetWorld()->CreateBody(&bodyDef);
}
b2Body* Projectile::GetRigidBody()
{
	return m_rigidBody;
}
