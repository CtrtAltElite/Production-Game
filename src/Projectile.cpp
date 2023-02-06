#include "Projectile.h"
#include "Camera.h"
#include "Game.h"
#include "TextureManager.h"
#include "Util.h"

Projectile::Projectile(Player* player)
{
	
	m_pPlayer = player;
	Start();
}
void Projectile::Draw()
{
	// draw the target
	TextureManager::Instance().Draw("projectile", GetTransform()->position, 0, 255, true);
}
void Projectile::Start()
{
	TextureManager::Instance().Load("../Assets/textures/Circle.png", "projectile");
	const auto size = TextureManager::Instance().GetTextureSize("projectile");
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));
	SDL_GetMouseState(&m_mousepos.x,&m_mousepos.y);
	isColliding = false;
	GetTransform()->position = m_pPlayer->GetTransform()->position;
	std::cout << "Spawned projectile at:" << GetTransform()->position.x << " , " << GetTransform()->position.y<<std::endl;
	GetRigidBody()->velocity-=Util::Normalize(glm::vec2{GetTransform()->position.x-m_mousepos.x,GetTransform()->position.y-m_mousepos.y});
	std::cout << GetRigidBody()->velocity.x << " , " << GetRigidBody()->velocity.y<<std::endl;
	SetType(GameObjectType::PROJECTILE);
}
void Projectile::Move()
{
	const float dt =Game::Instance().GetDeltaTime();
	const glm::vec2 initial_position = GetTransform()->position;
	const glm::vec2 velocity_term = GetRigidBody()->velocity * dt;
	const glm::vec2 acceleration_term = GetRigidBody()->acceleration * 0.5f *dt;
	const glm::vec2 final_position = initial_position + velocity_term + acceleration_term;
	GetTransform()->position = final_position;
	GetRigidBody()->velocity += GetRigidBody()->acceleration;
	GetRigidBody()->velocity = Util::Clamp(GetRigidBody()->velocity,GetMaxSpeed());
}
void Projectile::Update()
{
	Move();
}
void Projectile::Clean()
{
	
}

