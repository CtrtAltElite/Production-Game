#include "Projectile.h"

#include "Game.h"
#include "TextureManager.h"

Projectile::Projectile(Player* player)
{
	TextureManager::Instance().Load("../Assets/textures/Circle.png", "projectile");

	const auto size = TextureManager::Instance().GetTextureSize("projectile");
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));
	m_speed = 10.0f;
	m_maxvelo = 20.0f;
	SDL_GetMouseState(&mouseX, &mouseY);
	m_angle = (atan2((player->GetTransform()->position.y - mouseY)-Game::Instance().camera.y, (player->GetTransform()->position.x - mouseX) - Game::Instance().camera.x));
	GetTransform()->position = player->GetTransform()->position;
	GetRigidBody()->velocity = glm::vec2(-cos(m_angle), -sin(m_angle));
	GetRigidBody()->isColliding = false;

	SetType(GameObjectType::PROJECTILE);
	
}


void Projectile::Draw()
{
	// draw the target
	glm::vec2 position = GetTransform()->position;
	position.x -= Game::Instance().camera.x;
	position.y -= Game::Instance().camera.y;
	TextureManager::Instance().Draw("projectile", position, 0, 255, true);
}
void Projectile::Update()
{
	if (GetRigidBody()->velocity.x > m_maxvelo)
	{
		GetRigidBody()->velocity.x = m_maxvelo;
	}
	if (GetRigidBody()->velocity.x < -m_maxvelo)
	{
		GetRigidBody()->velocity.x = -m_maxvelo;
	}
	if (GetRigidBody()->velocity.y > m_maxvelo)
	{
		GetRigidBody()->velocity.y = m_maxvelo;
	}
	if (GetRigidBody()->velocity.y < -m_maxvelo)
	{
		GetRigidBody()->velocity.y = -m_maxvelo;
	}
	GetTransform()->position += GetRigidBody()->velocity * m_speed;
	
}
void Projectile::Clean()
{
	
}


