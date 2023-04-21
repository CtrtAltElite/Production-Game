#include "LandFish.h"
#include "TextureManager.h"
#include "Util.h"
#include "Game.h"
#include "Camera.h"

LandFish::LandFish()
{
    textureName = "LandFish";
    TextureManager::Instance().LoadSpriteSheet(
        "../Assets/sprites/obstacles/text/landfish.txt",
        "../Assets/sprites/obstacles/images/landFish.png",
        textureName
    );

    SetSpriteSheet(TextureManager::Instance().GetSpriteSheet(textureName));

    SetWidth(TextureManager::Instance().GetTextureSize(textureName).x);
    SetHeight(TextureManager::Instance().GetTextureSize(textureName).y);

    GetRigidBody()->mass = 1.0f;
    SetType(GameObjectType::LANDFISH);
    
    SetWidth(64);
    SetHeight(64);
    GetTransform()->position = glm::vec2(rand() % 200, rand() % 200);
    GetRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
    GetRigidBody()->bounds = glm::vec2(GetWidth(), GetHeight());
    GetRigidBody()->acceleration = glm::vec2(0.0f, 0.0);
    GetRigidBody()->isColliding = false;
    GetRigidBody()->mass = 5.0f;
    animVelo = 0.55f;

    BuildAnimations();
}

void LandFish::Draw()
{
    if (Game::Instance().GetDebugMode())
    {
        Util::DrawRect(Camera::Instance().CameraDisplace(this) -
            glm::vec2(this->GetWidth() * 0.5f, this->GetHeight() * 0.5f),
            this->GetWidth(), this->GetHeight());
    }

    TextureManager::Instance().PlayAnimation(textureName, GetAnimation("move"), Camera::Instance().CameraDisplace(this), animVelo, GetTransform()->rotation.r * Util::Rad2Deg - 180, 255, true, SDL_FLIP_VERTICAL);
}

void LandFish::Update()
{
}

void LandFish::Clean()
{
    Obstacle::Clean();
}

void LandFish::BuildAnimations()
{
    auto animation = Animation();

    animation.name = "idle";

    animation.frames.push_back(GetSpriteSheet()->GetFrame("idle1"));

    SetAnimation(animation);


    auto move_animation = Animation();
    move_animation.name = "move";
    move_animation.frames.push_back(GetSpriteSheet()->GetFrame("idle1"));
    move_animation.frames.push_back(GetSpriteSheet()->GetFrame("idle2"));
    move_animation.frames.push_back(GetSpriteSheet()->GetFrame("idle3"));
    move_animation.frames.push_back(GetSpriteSheet()->GetFrame("idle4"));
    move_animation.frames.push_back(GetSpriteSheet()->GetFrame("idle5"));
    move_animation.frames.push_back(GetSpriteSheet()->GetFrame("idle6"));
    move_animation.frames.push_back(GetSpriteSheet()->GetFrame("idle7"));
    move_animation.frames.push_back(GetSpriteSheet()->GetFrame("idle8"));


    SetAnimation(move_animation);
}
