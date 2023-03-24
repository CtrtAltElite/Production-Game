#include "Background.h"

#include "Camera.h"
#include "Game.h"
#include "TextureManager.h"




// Default Constructor... Might remove code in here later
Background::Background()
{
	TextureManager::Instance().Load("../Assets/textures/ocean.gif", "background");

	const auto size = TextureManager::Instance().GetTextureSize("background");
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));
	SetType(GameObjectType::BACKGROUND);

	m_key = "background";
}

Background::Background(std::string imgFile, std::string key)
{
	TextureManager::Instance().Load(imgFile, key);

	const auto size = TextureManager::Instance().GetTextureSize(key);
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));
	SetType(GameObjectType::BACKGROUND);

	m_key = key;
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
			TextureManager::Instance().Draw(m_key, temp.x+GetHeight()*i, temp.y+GetWidth()*p);
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

