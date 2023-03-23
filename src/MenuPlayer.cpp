#include "MenuPlayer.h"

#include "Camera.h"
#include "Util.h"

MenuPlayer::MenuPlayer()
{
	SetWidth(100);
	SetHeight(50);

	GetTransform()->position = glm::vec2(0.0f, 300.0f);
	GetRigidBody()->bounds = glm::vec2(GetWidth(), GetHeight());
	GetRigidBody()->isColliding = false;
	SetType(GameObjectType::PLAYER);
}

MenuPlayer::~MenuPlayer()
= default;

void MenuPlayer::Draw()
{
	Util::DrawRect(glm::vec2(GetWidth() * 0.5f, GetHeight() * 0.5f), GetWidth(), GetHeight());
}

void MenuPlayer::Update()
{
}

void MenuPlayer::Clean()
{
}

void MenuPlayer::Move()
{
}
