#include "Background.h"

#include "Game.h"
#include "TextureManager.h"
Background::Background()
{
	TextureManager::Instance().Load("../Assets/textures/nebula.png", "background");

	SetWidth(1280);
	SetHeight(720);
	GetTransform()->position = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->velocity = glm::vec2(0, 0);
	GetRigidBody()->isColliding = false;
	SetType(GameObjectType::BACKGROUND);
}
Background::~Background()
= default;


void Background::Draw()
{
	// alias for x and y
	const auto x = static_cast<int>(GetTransform()->position.x - Game::Instance().camera.x);
	const auto y = static_cast<int>(GetTransform()->position.y - Game::Instance().camera.y);
	TextureManager::Instance().Draw("background",x,y);
}
void Background::Update()
{
	
}

void Background::Clean()
{
	
}

