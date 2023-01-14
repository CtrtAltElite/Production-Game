#include "Projectile.h"
#include "TextureManager.h"

Projectile::Projectile()
{
	TextureManager::Instance().Load("../Assets/textures/Circle.png", "circle");

	const auto size = TextureManager::Instance().GetTextureSize("circle");
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));
	GetTransform()->position = glm::vec2(100.0f, 100.0f);
	GetRigidBody()->velocity = glm::vec2(0, 0);
	GetRigidBody()->isColliding = false;

	SetType(GameObjectType::PROJECTILE);
	
}
Projectile::~Projectile()
	= default;

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


