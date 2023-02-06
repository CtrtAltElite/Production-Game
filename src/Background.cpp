#include "Background.h"

#include "Camera.h"
#include "Game.h"
#include "TextureManager.h"

Background::Background()
{
	TextureManager::Instance().Load("../Assets/textures/ocean.gif", "background");

	const auto size = TextureManager::Instance().GetTextureSize("background");
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));
	SetType(GameObjectType::BACKGROUND);
}
Background::~Background()
= default;


void Background::Draw()
{
	// alias for x and y
	const auto x = static_cast<int>(GetTransform()->position.x);
	const auto y = static_cast<int>(GetTransform()->position.y);
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

