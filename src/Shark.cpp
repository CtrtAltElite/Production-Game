﻿#include "Shark.h"

#include "Camera.h"
#include "Game.h"
#include "TextureManager.h"
#include "Util.h"

Shark::Shark()
{
    TextureManager::Instance().Load("../Assets/textures/Brute_Shark.png", "shark");
    TextureManager::Instance().LoadSpriteSheet(
        "../Assets/sprites/shark_sprite.txt",
        "../Assets/sprites/Brute_Sharkanimatedsheet.png", 
        "shark_spritesheet");
    SetSpriteSheet(TextureManager::Instance().GetSpriteSheet("shark_spritesheet"));
    auto animation = Animation();

    animation.name = "move";
    animation.frames.push_back(GetSpriteSheet()->GetFrame("shark1"));
    animation.frames.push_back(GetSpriteSheet()->GetFrame("shark2"));
    animation.frames.push_back(GetSpriteSheet()->GetFrame("shark3"));
    animation.frames.push_back(GetSpriteSheet()->GetFrame("shark4"));
    animation.frames.push_back(GetSpriteSheet()->GetFrame("shark5"));
    animation.frames.push_back(GetSpriteSheet()->GetFrame("shark6"));
    animation.frames.push_back(GetSpriteSheet()->GetFrame("shark7"));
    animation.frames.push_back(GetSpriteSheet()->GetFrame("shark8"));

    SetAnimation(animation);
    SetWidth(53);
    SetHeight(40);
    SetHealth(100.0f);
    SetAttackDamage(30.0f);
    GetTransform()->position = glm::vec2(rand() % 500, Game::Instance().GetPlayer()->GetTransform()->position.y+Config::SCREEN_HEIGHT);
    GetRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
    GetRigidBody()->bounds=glm::vec2(GetWidth(), GetHeight());
    GetRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
    GetRigidBody()->isColliding = false;
    GetRigidBody()->mass = 8.0f;
    SetSpeed(120.0f);
    animVelo = 0.33f;
    SetType(GameObjectType::SHARK);
}

void Shark::Draw()
{
    if(Game::Instance().GetDebugMode())
    {
        Util::DrawRect(Camera::Instance().CameraDisplace(this) -
                glm::vec2(static_cast<float>(this->GetWidth()) * 0.5f, static_cast<float>(this->GetHeight()) * 0.5f),
                this->GetWidth(), this->GetHeight());
    }
    //SDL_RenderDrawRectF(Renderer::Instance().GetRenderer(),new SDL_FRect{Camera::Instance().CameraDisplace(this).x,Camera::Instance().CameraDisplace(this).y,static_cast<float>(GetWidth()),static_cast<float>(GetHeight())});
    if(GetFlipped())
    {
        //TextureManager::Instance().PlayAnimation("shark_spritesheet", GetAnimation("default") ,Camera::Instance().CameraDisplace(this),GetTransform()->rotation.r*Util::Rad2Deg-180, 255, true);
        TextureManager::Instance().PlayAnimation("shark_spritesheet", GetAnimation("move"), Camera::Instance().CameraDisplace(this), animVelo, GetTransform()->rotation.r * Util::Rad2Deg - 180.0f, 255, true);
    }
    else
    {
        //TextureManager::Instance().PlayAnimation("shark_spritesheet", GetAnimation("default") ,Camera::Instance().CameraDisplace(this),GetTransform()->rotation.r*Util::Rad2Deg-180, 255, true,SDL_FLIP_VERTICAL);
        TextureManager::Instance().PlayAnimation("shark_spritesheet", GetAnimation("move"), Camera::Instance().CameraDisplace(this), animVelo, GetTransform()->rotation.r * Util::Rad2Deg - 180.0f, 255, true, SDL_FLIP_VERTICAL);

    }
    
    
    
}

void Shark::Update()
{
    Move();
    
    if(GetHealth()<=0)
    {
        SetIsDead(true);
    }
    if(GetIsDead())
    {
        //do death stuff
        //play death animation
        SetDeleteMe(true);
    }
}

void Shark::Clean()
{
}

void Shark::TakeDamage(float damage)
{
    SetHealth(GetHealth()-damage);
    
}
