#include "StartButton.h"
#include "Game.h"

StartButton::StartButton()
	// call super constructor
	:Button(
		"../Assets/textures/StartButton.png",
		"startButton",
		GameObjectType::START_BUTTON, glm::vec2(400.0f, 300.0f)), m_isClicked(false)
{
	
}

StartButton::~StartButton()
= default;


bool StartButton::ButtonClick()
{
	if (m_mouseOver && m_leftMouseButtonClicked)
	{
		if(!m_isClicked)
		{
			Game::Instance().ChangeSceneState(SceneState::LS1);
			m_isClicked = true;
		}
		return true;
	}
	else
	{
		m_isClicked = false;
	}

	return false;
}


