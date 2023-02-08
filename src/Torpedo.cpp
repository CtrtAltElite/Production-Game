#include "Torpedo.h"
#include "Projectile.h"
#include "Camera.h"
#include "Game.h"
#include "TextureManager.h"
#include "Util.h"

Torpedo::Torpedo(Player* player)
{
	
    SetPlayer(player);
    Start();
}
void Torpedo::Draw()
{
    // draw the target
    TextureManager::Instance().Draw("torpedo", Camera::Instance().CameraDisplace(GetTransform()->position), GetAngle()*Util::Rad2Deg, 255, true);
}
void Torpedo::Start()
{
    TextureManager::Instance().Load("../Assets/textures/Small_Torpedo.png", "torpedo");
    const auto size = TextureManager::Instance().GetTextureSize("torpedo");
    SetWidth(static_cast<int>(size.x));
    SetHeight(static_cast<int>(size.y));
    SetVeloDamp({0.9975,0.9975});
    SetSpeed(150.0f);
    SetMaxSpeed(300.0f);
    m_mousePos = Util::GetMousePos();
    SetIsColliding(false);
    SetAngle(GetPlayer()->GetTransform()->rotation.r);
    GetTransform()->position = GetPlayer()->GetTransform()->position;
    GetRigidBody()->velocity+= glm::vec2{cos(GetPlayer()->GetTransform()->rotation.r)*GetSpeed(),sin(GetPlayer()->GetTransform()->rotation.r)*GetSpeed()};
    SetType(GameObjectType::PROJECTILE);

    //debug
    std::cout << "Spawned projectile at:" << GetTransform()->position.x << " , " << GetTransform()->position.y<<std::endl;
    std::cout << GetRigidBody()->velocity.x << " , " << GetRigidBody()->velocity.y<<std::endl;
}
void Torpedo::Move()
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
void Torpedo::Update()
{
    Move();
    GetRigidBody()->velocity*=GetVeloDamp();
}
void Torpedo::Clean()
{
	
}

