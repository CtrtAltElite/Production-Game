#include "Shark.h"

#include "Camera.h"
#include "Game.h"
#include "Renderer.h"
#include "TextureManager.h"
#include "Util.h"

Shark::Shark()
{
    TextureManager::Instance().Load("../Assets/textures/Brute_Shark.png", "shark");
    SetWidth(53.0f);
    SetHeight(40.0f);
    SetHealth(100.0f);
    GetTransform()->position = glm::vec2(200.0f, 200.0f);
    GetRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
    GetRigidBody()->bounds=glm::vec2(GetWidth(), GetHeight());
    GetRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
    GetRigidBody()->isColliding = false;
    SetType(GameObjectType::SHARK);
}

void Shark::Draw()
{
    if(Game::Instance().GetDebugMode())
    {
        Util::DrawRect(Camera::Instance().CameraDisplace(this) -
                glm::vec2(this->GetWidth() * 0.5f, this->GetHeight() * 0.5f),
                this->GetWidth(), this->GetHeight());
    }
    //SDL_RenderDrawRectF(Renderer::Instance().GetRenderer(),new SDL_FRect{Camera::Instance().CameraDisplace(this).x,Camera::Instance().CameraDisplace(this).y,static_cast<float>(GetWidth()),static_cast<float>(GetHeight())});
    TextureManager::Instance().Draw("shark", Camera::Instance().CameraDisplace(this),0, 255, true);
}

void Shark::Update()
{
    Move();
    if(GetHealth()<=0)
    {
        SetIsDead(true);
    }
}

void Shark::Clean()
{
}
