#include "Background.h"

#include "Game.h"
#include "TextureManager.h"
Background::Background()
{
	TextureManager::Instance().Load("../Assets/textures/ocean.gif", "background");

	const auto size = TextureManager::Instance().GetTextureSize("background");
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));
	SetType(GameObjectType::BACKGROUND);
	InitRigidBody(b2Vec2(0.0f,0.0f));
}
Background::~Background()
= default;


void Background::Draw()
{
	// alias for x and y
	const auto x = static_cast<int>(m_rigidBody->GetPosition().x - Game::Instance().camera.x);
	const auto y = static_cast<int>(m_rigidBody->GetPosition().y - Game::Instance().camera.y);
	for (int i =-10 ;i<10;i++)
	{
		for(int p = -10; p<10; p++)
		{
			TextureManager::Instance().Draw("background", x+GetHeight()*i, y+GetWidth()*p, 90);
		}
	}
	
}
void Background::Update()
{
	
}

void Background::Clean()
{
	
}
void Background::InitRigidBody(b2Vec2 position)
{
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(position.x, position.y);
	m_rigidBody = Game::Instance().world->CreateBody(&bodyDef);
}
b2Body* Background::GetRigidBody()
{
	return m_rigidBody;
}
