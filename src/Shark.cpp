#include "Shark.h"
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
    TextureManager::Instance().Draw("shark", GetTransform()->position,0, 255, true);
}

void Shark::Update()
{
    Move();
}

void Shark::Clean()
{
}
