#include "MenuPlayer.h"

#include "Camera.h"
#include "Util.h"
#include "TextureManager.h"
#include "Game.h"

MenuPlayer::MenuPlayer()
{
	TextureManager::Instance().LoadSpriteSheet(
		"../Assets/sprites/player/redDino.txt",
		"../Assets/sprites/player/redDino.png",
		"dino_spritesheet"
	);

	SetSpriteSheet(TextureManager::Instance().GetSpriteSheet("dino_spritesheet"));
	SetWidth(24);
	SetHeight(24);

	GetTransform()->position = glm::vec2(Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2);
	GetRigidBody()->bounds = glm::vec2(GetWidth(), GetHeight());
	GetRigidBody()->isColliding = false;


	SetType(GameObjectType::PLAYER);

	BuildAnimations();
}

MenuPlayer::~MenuPlayer()
= default;

void MenuPlayer::Draw()
{
	if (Game::Instance().GetDebugMode()) {
		Util::DrawRect(Camera::Instance().CameraDisplace(this) -
			glm::vec2(GetWidth() * 0.5f, GetHeight() * 0.5f), GetWidth(), GetHeight());
	}
	

	TextureManager::Instance().PlayAnimation("dino_spritesheet", GetAnimation("idle"),
		Camera::Instance().CameraDisplace(this), 0.33f, 0, 255, true);
}

void MenuPlayer::Update()
{

	
}

void MenuPlayer::Clean()
{
}

void MenuPlayer::Move(bool isLeft)
{
	glm::vec2 final_position = GetTransform()->position;
	if (isLeft) {
		final_position.x -= 5.0f;
	}
	else { // isRight
		final_position.x += 5.0f;
	}

	GetTransform()->position = final_position;


	Camera::Instance().GetTransform()->position.x = GetTransform()->position.x - static_cast<float>(Config::SCREEN_WIDTH) / 2;
	Camera::Instance().GetTransform()->position.y = GetTransform()->position.y - static_cast<float>(Config::SCREEN_HEIGHT) / 2;

}

void MenuPlayer::BuildAnimations()
{
	auto idle_animation = Animation();

	idle_animation.name = "idle";
	idle_animation.frames.push_back(GetSpriteSheet()->GetFrame("idle1"));
	idle_animation.frames.push_back(GetSpriteSheet()->GetFrame("idle2"));
	idle_animation.frames.push_back(GetSpriteSheet()->GetFrame("idle3"));
	idle_animation.frames.push_back(GetSpriteSheet()->GetFrame("idle4"));
	
	SetAnimation(idle_animation);
}
