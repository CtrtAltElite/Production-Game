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
	TextureManager::Instance().Draw("projectile", Camera::Instance().CameraDisplace(GetTransform()->position), m_angle*Util::Rad2Deg, 255, true);
}
void Projectile::Start()
{
	TextureManager::Instance().Load("../Assets/textures/Small_Torpedo.png", "projectile");
	const auto size = TextureManager::Instance().GetTextureSize("projectile");
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));
	veloDamp = {0.9975,0.9975};
	m_speed = 150.0f;
	m_maxSpeed = 300.0f;
	SDL_GetMouseState(&m_mousepos.x,&m_mousepos.y);
	isColliding = false;
	m_angle = m_pPlayer->GetTransform()->rotation.r;
	GetTransform()->position = m_pPlayer->GetTransform()->position;
	GetRigidBody()->velocity+= glm::vec2{cos(m_pPlayer->GetTransform()->rotation.r)*m_speed,sin(m_pPlayer->GetTransform()->rotation.r)*m_speed};
	SetType(GameObjectType::PROJECTILE);

	//debug
	std::cout << "Spawned projectile at:" << GetTransform()->position.x << " , " << GetTransform()->position.y<<std::endl;
	std::cout << GetRigidBody()->velocity.x << " , " << GetRigidBody()->velocity.y<<std::endl;
}
void Projectile::Move()
{
	const float dt =Game::Instance().GetDeltaTime();
	const glm::vec2 initial_position = GetTransform()->position;
	const glm::vec2 velocity_term = GetRigidBody()->velocity * dt;
	const glm::vec2 acceleration_term = GetRigidBody()->acceleration * 0.5f;
	const glm::vec2 final_position = initial_position + velocity_term + acceleration_term;
	GetTransform()->position = final_position;
	GetRigidBody()->velocity += GetRigidBody()->acceleration;
	GetRigidBody()->velocity = Util::Clamp(GetRigidBody()->velocity,GetMaxSpeed());
}
void Projectile::Update()
{
	Move();
	GetRigidBody()->velocity*=veloDamp;
}
void Projectile::Clean()
{
	
}

