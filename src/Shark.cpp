#include "Shark.h"

#include "Camera.h"
#include "Renderer.h"
#include "TextureManager.h"

Shark::Shark()
{
    TextureManager::Instance().Load("../Assets/textures/Brute_Shark.png", "shark");
    SetWidth(50.0f);
    SetHeight(50.0f);
    GetTransform()->position = glm::vec2(200.0f, 200.0f);
    GetRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
    GetRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
    GetRigidBody()->isColliding = false;
    SetType(GameObjectType::SHARK);
}

void Shark::Draw()
{
    SDL_RenderDrawRectF(Renderer::Instance().GetRenderer(),new SDL_FRect{Camera::Instance().CameraDisplace(GetTransform()->position).x,Camera::Instance().CameraDisplace(GetTransform()->position).y,static_cast<float>(GetWidth()),static_cast<float>(GetHeight())});
    TextureManager::Instance().Draw("shark", Camera::Instance().CameraDisplace(GetTransform()->position),0, 255, true);
}

void Shark::Update()
{
    Move();
}

void Shark::Clean()
{
}
