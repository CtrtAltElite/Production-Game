#include "RestartButton.h"
#include "Game.h"

RestartButton::RestartButton()
// call super constructor
	:Button(
		"../Assets/textures/restartButton.png",
		"restartButton",
		GameObjectType::RESTART_BUTTON, glm::vec2(320.0f, 400.0f)), m_isClicked(false)
{

}

RestartButton::~RestartButton()
{
}

bool RestartButton::ButtonClick()
{
	if (m_mouseOver() && m_leftMouseButtonClicked)
	{
		if (!m_isClicked)
		{
			ScoreBoardManager::Instance()->Start();
			ScoreBoardManager::Instance()->setLives(5);
			ScoreBoardManager::Instance()->setScore(0);
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
