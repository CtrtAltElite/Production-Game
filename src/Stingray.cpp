#include "Stingray.h"

#include "Camera.h"
#include "Game.h"
#include "Util.h"
#include "TextureManager.h"

Stingray::Stingray()
{
    textureName = "stingray";
    TextureManager::Instance().LoadSpriteSheet(
        "../Assets/sprites/obstacles/text/stingray.txt",
        "../Assets/sprites/obstacles/images/stingray.png",
        textureName
    );

    SetSpriteSheet(TextureManager::Instance().GetSpriteSheet(textureName));
    auto animation = Animation();

    animation.name = "move";
    animation.frames.push_back(GetSpriteSheet()->GetFrame("stingray1"));
    animation.frames.push_back(GetSpriteSheet()->GetFrame("stingray2"));
    animation.frames.push_back(GetSpriteSheet()->GetFrame("stingray3"));
    animation.frames.push_back(GetSpriteSheet()->GetFrame("stingray4"));

    SetAnimation(animation);
    SetWidth(64);
    SetHeight(64);
    GetTransform()->position = glm::vec2(rand() % 200, rand() % 200);
    GetRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
    GetRigidBody()->bounds = glm::vec2(GetWidth(), GetHeight());
    GetRigidBody()->acceleration = glm::vec2(0.0f, 0.0);
    GetRigidBody()->isColliding = false;
    GetRigidBody()->mass = 5.0f;
    animVelo = 0.55f;
}

void Stingray::Draw()
{
    if (Game::Instance().GetDebugMode())
    {
        Util::DrawRect(Camera::Instance().CameraDisplace(this) -
            glm::vec2(this->GetWidth() * 0.5f, this->GetHeight() * 0.5f),
            this->GetWidth(), this->GetHeight());
    }
    TextureManager::Instance().PlayAnimation(textureName, GetAnimation("move"), Camera::Instance().CameraDisplace(this), animVelo, GetTransform()->rotation.r * Util::Rad2Deg - 180, 255, true);

    //if (GetFlipped())
    //{
    //    //TextureManager::Instance().PlayAnimation("shark_spritesheet", GetAnimation("default") ,Camera::Instance().CameraDisplace(this),GetTransform()->rotation.r*Util::Rad2Deg-180, 255, true);
    //    TextureManager::Instance().PlayAnimation("stingray_spritesheet", GetAnimation("move"), Camera::Instance().CameraDisplace(this), animVelo, GetTransform()->rotation.r * Util::Rad2Deg - 180, 255, true);
	//}
    //else
    //{
    //    //TextureManager::Instance().PlayAnimation("shark_spritesheet", GetAnimation("default") ,Camera::Instance().CameraDisplace(this),GetTransform()->rotation.r*Util::Rad2Deg-180, 255, true,SDL_FLIP_VERTICAL);
    //    TextureManager::Instance().PlayAnimation("stingray_spritesheet", GetAnimation("move"), Camera::Instance().CameraDisplace(this), animVelo, GetTransform()->rotation.r * Util::Rad2Deg - 180, 255, true, SDL_FLIP_VERTICAL);

    //}
}

void Stingray::Update()
{
    GetTransform()->position.x += 2.0f;
}

void Stingray::Clean()
{
}
