#include "Projectile.h"

#include "Game.h"
#include "TextureManager.h"

Projectile::Projectile(Player* player)
{
	TextureManager::Instance().Load("../Assets/textures/Circle.png", "projectile");

	const auto size = TextureManager::Instance().GetTextureSize("projectile");
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));
	m_maxvelo = 20.0f;
	SDL_GetMouseState(&mouseX, &mouseY);
	m_angle = (atan2((player->GetRigidBody()->GetPosition().y - mouseY)-Game::Instance().camera.y, (player->GetRigidBody()->GetPosition().x - mouseX) - Game::Instance().camera.x));
	GetRigidBody()->SetTransform(player->GetRigidBody()->GetPosition(), GetRigidBody()->GetAngle());
	//GetRigidBody()->GetLinearVelocity() = b2Vec2(-cos(m_angle)*10.0f, -sin(m_angle)*10.0f);
	//player->GetRigidBody()->GetLinearVelocity() += (cos(m_angle)*3.0f, sin(m_angle)*3.0f);
	isColliding = false;

	SetType(GameObjectType::PROJECTILE);
	
}


void Projectile::Draw()
{
	// draw the target
	b2Vec2 position = GetRigidBody()->GetPosition();
	position.x -= Game::Instance().camera.x;
	position.y -= Game::Instance().camera.y;
	TextureManager::Instance().Draw("projectile", position, 0, 255, true);
}
void Projectile::Update()
{
	/*
	if (GetRigidBody()->GetLinearVelocity().x > m_maxvelo)
	{
		GetRigidBody()->GetLinearVelocity().x = m_maxvelo;
	}
	if (GetRigidBody()->GetLinearVelocity().x < -m_maxvelo)
	{
		GetRigidBody()->GetLinearVelocity().x = -m_maxvelo;
	}
	if (GetRigidBody()->GetLinearVelocity().y > m_maxvelo)
	{
		GetRigidBody()->GetLinearVelocity().y = m_maxvelo;
	}
	if (GetRigidBody()->GetLinearVelocity().y < -m_maxvelo)
	{
		GetRigidBody()->GetLinearVelocity().y = -m_maxvelo;
	}
	GetRigidBody()->GetPosition() += GetRigidBody()->GetLinearVelocity();
	*/
	//use box2d physics instead..!!!
	
}
void Projectile::Clean()
{
	
}
void Projectile::InitRigidBody()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(0.0f,0.0f);
	bodyDef.enabled = true;
	m_rigidBody = Game::Instance().world->CreateBody(&bodyDef);
}

