#include "LevelSelectionObject.h"

#include "TextureManager.h"
#include "Game.h"
#include "Camera.h"
#include "Util.h"


LevelSelectionObject::LevelSelectionObject() 
{
	TextureManager::Instance().Load("../Assets/textures/obstacle.png", "obstacle");
	TextureManager::Instance().Load(startText, startTextName);


	const auto size = TextureManager::Instance().GetTextureSize("obstacle");

	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));

	GetTransform()->position = glm::vec2(0, 0);
	GetRigidBody()->bounds = glm::vec2(GetWidth(), GetHeight());
	GetRigidBody()->mass = 0.0f; // Infinite mass.

	SetIsCentered(true);
	SetType(GameObjectType::OBSTACLE);
	GetRigidBody()->isColliding = false;
	SetDeleteMe(false);


	tag = "LevelSelector";
}

LevelSelectionObject::LevelSelectionObject(const char* texture, const char* fileName)
{
	TextureManager::Instance().Load(texture, fileName);
	TextureManager::Instance().Load(startText, startTextName);


	textureName = fileName;

	const auto size = TextureManager::Instance().GetTextureSize(fileName);
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));

	GetTransform()->position = glm::vec2(0, 0);
	GetRigidBody()->bounds = glm::vec2(GetWidth(), GetHeight());
	GetRigidBody()->mass = 0.0f; // Infinite mass.

	SetIsCentered(true);
	SetType(GameObjectType::OBSTACLE);
	GetRigidBody()->isColliding = false;
	SetDeleteMe(false);


	tag = "levelSelector";
}

LevelSelectionObject::~LevelSelectionObject()
= default;

void LevelSelectionObject::Draw()
{
	if (Game::Instance().GetDebugMode())
	{
		Util::DrawRect(Camera::Instance().CameraDisplace(this) -
			glm::vec2(this->GetWidth() * 0.5f, this->GetHeight() * 0.5f),
			this->GetWidth(), this->GetHeight());

	}
	TextureManager::Instance().Draw(textureName, Camera::Instance().CameraDisplace(this), 0, 255, true);
	
	// Drawing the label if it is visible
	if (m_isLabelEnabled) {
		TextureManager::Instance().Draw(startTextName, Camera::Instance().CameraDisplace(this) - glm::vec2(0, 70.0f), 0, 255, true);
	}
}

void LevelSelectionObject::Update()
{
}

void LevelSelectionObject::Clean()
{
}

void LevelSelectionObject::SetLabel(bool value)
{
	m_isLabelEnabled = value;
}

bool LevelSelectionObject::GetLabel()
{
	return m_isLabelEnabled;
}

void LevelSelectionObject::SetState(SceneState state)
{
	m_stateToChange = state;
}

SceneState LevelSelectionObject::GetState()
{
	return m_stateToChange;
}


