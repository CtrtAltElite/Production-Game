#include "Projectile.h"
#include "TextureManager.h"

Projectile::Projectile(Player* player,SDL_Point mousePosition)
{
	TextureManager::Instance().Load("../Assets/textures/Circle.png", "projectile");

	const auto size = TextureManager::Instance().GetTextureSize("projectile");
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));
	std::cout << mousePosition.x << std::endl;
	std::cout << mousePosition.y << std::endl;
	m_speed = 5.0f;
	m_angle = (atan2((player->GetTransform()->position.y - mousePosition.y), (player->GetTransform()->position.x - mousePosition.x)));
	GetTransform()->position = player->GetTransform()->position;
	GetRigidBody()->velocity = glm::vec2(-cos(m_angle), -sin(m_angle));
	GetRigidBody()->isColliding = false;

	SetType(GameObjectType::PROJECTILE);
	
}


void Projectile::Draw()
{
	// draw the target
	TextureManager::Instance().Draw("projectile", GetTransform()->position, 0, 255, true);
}
void Projectile::Update()
{
	GetTransform()->position += GetRigidBody()->velocity * m_speed;
	
}
void Projectile::Clean()
{
	
}


