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
	glm::vec2 temp = Camera::Instance().CameraDisplace(this);
	for (int i =-10 ;i<10;i++)
	{
		for(int p = -10; p<10; p++)
		{
			TextureManager::Instance().Draw("background", temp.x+GetHeight()*i, temp.y+GetWidth()*p, 90);
			//better way to do this
		}
	}
	
}
void Background::Update()
{
	
}

void Background::Clean()
{
	
}

