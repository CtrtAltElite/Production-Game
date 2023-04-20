#include "Jellyfish.h"

#include "Camera.h"
#include "Game.h"
#include "Util.h"
#include "TextureManager.h"

Jellyfish::Jellyfish()
{
	textureName = "JellyFish";
	TextureManager::Instance().LoadSpriteSheet(
		"../Assets/sprites/obstacles/text/jellyfish.txt",
		"../Assets/sprites/obstacles/images/jellyfish.png",
		textureName
	);
	SetSpriteSheet(TextureManager::Instance().GetSpriteSheet(textureName));

	auto animation = Animation();

	animation.name = "idle";
	animation.frames.push_back(GetSpriteSheet()->GetFrame("jellyfish4"));
	SetAnimation(animation);

	animation = Animation();
	animation.name = "move";
	animation.frames.push_back(GetSpriteSheet()->GetFrame("jellyfish1"));
	animation.frames.push_back(GetSpriteSheet()->GetFrame("jellyfish2"));
	animation.frames.push_back(GetSpriteSheet()->GetFrame("jellyfish3"));
	animation.frames.push_back(GetSpriteSheet()->GetFrame("jellyfish4"));

	SetAnimation(animation);
	SetWidth(32);
	SetHeight(32);
	GetRigidBody()->mass = 1.0f;
	animVelo = 0.22f;
	SetType(GameObjectType::JELLYFISH);
}

void Jellyfish::Draw()
{
	if (Game::Instance().GetDebugMode())
	{
		Util::DrawRect(Camera::Instance().CameraDisplace(this) -
			glm::vec2(this->GetWidth() * 0.5f, this->GetHeight() * 0.5f),
			this->GetWidth(), this->GetHeight());
	}
	//SDL_RenderDrawRectF(Renderer::Instance().GetRenderer(),new SDL_FRect{Camera::Instance().CameraDisplace(this).x,Camera::Instance().CameraDisplace(this).y,static_cast<float>(GetWidth()),static_cast<float>(GetHeight())});
	TextureManager::Instance().PlayAnimation(textureName, GetAnimation("move"), Camera::Instance().CameraDisplace(this), animVelo, GetTransform()->rotation.r * Util::Rad2Deg - 180, 255, true);
}

void Jellyfish::Update()
{
	GetTransform()->position.y += 1.0f;
}

void Jellyfish::Clean()
{
	Obstacle::Clean();
}
