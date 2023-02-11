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
    Util::DrawRect(Camera::Instance().CameraDisplace(this) -
            glm::vec2(this->GetWidth() * 0.5f, this->GetHeight() * 0.5f),
            this->GetWidth(), this->GetHeight());
    // draw the target
    TextureManager::Instance().Draw("torpedo", Camera::Instance().CameraDisplace(this), GetAngle()*Util::Rad2Deg, 255, true);
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
    SetDeleteBuffer(100.0f);
    SetDamage(50.0f);
    SetProjectileSource(GetPlayer());
    SetAngle(GetPlayer()->GetTransform()->rotation.r);
    GetRigidBody()->velocity+= glm::vec2{cos(GetPlayer()->GetTransform()->rotation.r)*GetSpeed(),sin(GetPlayer()->GetTransform()->rotation.r)*GetSpeed()};
    GetTransform()->position = GetPlayer()->GetTransform()->position;
    SetType(GameObjectType::PROJECTILE);

    //debug
    //std::cout << "Spawned projectile at:" << GetTransform()->position.x << " , " << GetTransform()->position.y<<std::endl;
    //std::cout << GetRigidBody()->velocity.x << " , " << GetRigidBody()->velocity.y<<std::endl;
}
void Torpedo::Update()
{
    Move();
    //GetRigidBody()->velocity*=GetVeloDamp();
    CheckBounds();
    if(GetIsColliding())
    {
        SetDeleteMe(true);
    }
}
void Torpedo::Clean()
{
	
}

