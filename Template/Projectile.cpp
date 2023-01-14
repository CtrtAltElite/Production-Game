#include "Projectile.h"
#include "TextureManager.h"

Projectile::Projectile(Player* player)
{
	TextureManager::Instance().Load("../Assets/textures/Circle.png", "projectile");

	const auto size = TextureManager::Instance().GetTextureSize("projectile");
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));
	GetTransform()->position = player->GetTransform()->position;
	GetRigidBody()->velocity = glm::vec2(0, 0);
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
	
}
void Projectile::Clean()
{
	
}


