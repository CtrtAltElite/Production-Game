#include "Background.h"

#include "Camera.h"
#include "Game.h"
#include "TextureManager.h"
#include "WorldManager.h"

Background::Background()
{
	TextureManager::Instance().Load("../Assets/textures/ocean.gif", "background");

	const auto size = TextureManager::Instance().GetTextureSize("background");
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));
	SetType(GameObjectType::BACKGROUND);
	InitRigidBody();
}
Background::~Background()
= default;


void Background::Draw()
{
	// alias for x and y
	b2Vec2 position = Camera::Instance().CameraDisplace(m_rigidBody->GetPosition());
	for (int i =-10 ;i<10;i++)
	{
		for(int p = -10; p<10; p++)
		{
			TextureManager::Instance().Draw("background", position.x+GetHeight()*i, position.y+GetWidth()*p, 90);
		}
	}
	
}
void Background::Update()
{
	
}

void Background::Clean()
{
	
}
void Background::InitRigidBody()
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(0.0f, 0.0f);
	bodyDef.enabled = true;
	m_rigidBody = WorldManager::Instance().GetWorld()->CreateBody(&bodyDef);
}
b2Body* Background::GetRigidBody()
{
	return m_rigidBody;
}