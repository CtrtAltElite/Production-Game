#include "LevelManager.h"

// Static variable initializers :)
std::array<Scene*, static_cast<int>(SceneState::NUM_OF_SCENES)> LevelManager::m_levelScreens;
Scene* LevelManager::m_pCurrentLevel;
bool LevelManager::m_isPaused;
bool LevelManager::m_isGameOver;

// Default constructor and destructor.
LevelManager::LevelManager()
= default;

LevelManager::~LevelManager()
= default;

// Initializes anything that has to be initialized
void LevelManager::Init()
{
	InitLevelSelectionScreens();
	m_pCurrentLevel = m_levelScreens[static_cast<int>(SceneState::START)]; // Setting to start scene.
	m_pCurrentLevel->Start();
}

// Changes level.
void LevelManager::ChangeLevelSelection(SceneState state_to_change)
{
	if (m_levelScreens[static_cast<int>(state_to_change)] != nullptr) {
		m_pCurrentLevel = m_levelScreens[static_cast<int>(state_to_change)];
		m_pCurrentLevel->Start();
	}
	else {
		std::cout << "Error, Scene does not exist.\n\n";
	}

}

// Updates anything inside the current level.
void LevelManager::UpdateLevel()
{
	m_pCurrentLevel->HandleEvents();
	m_pCurrentLevel->Update();

	if (m_isPaused) {
		m_levelScreens[static_cast<int>(SceneState::PAUSE)]->HandleEvents();
		m_levelScreens[static_cast<int>(SceneState::PAUSE)]->Update();
	}
	if (m_isGameOver)
	{
		m_levelScreens[static_cast<int>(SceneState::GAME_OVER)]->HandleEvents();
		m_levelScreens[static_cast<int>(SceneState::GAME_OVER)]->Update();
	}
}

void LevelManager::SetPause(bool value)
{
	m_isPaused = value;
	if (m_isPaused) {
		m_levelScreens[static_cast<int>(SceneState::PAUSE)]->Start();
	}
}

bool LevelManager::IsLevelPaused()
{
	return m_isPaused;
}

void LevelManager::SetGameOver(bool value)
{
	m_isGameOver = value;
	if (m_isGameOver)
	{
		m_levelScreens[static_cast<int>(SceneState::GAME_OVER)]->Start();
	}
}

bool LevelManager::IsGameOver()
{
	return m_isGameOver;
}

// Renders the current level.
void LevelManager::RenderLevel()
{
	m_pCurrentLevel->Draw();
	if (m_isPaused) {
		m_levelScreens[static_cast<int>(SceneState::PAUSE)]->Draw();
	}
	if (m_isGameOver)
	{
		m_levelScreens[static_cast<int>(SceneState::GAME_OVER)]->Draw();
	}
}

void LevelManager::ExitLevel()
{
	m_pCurrentLevel->Clean();
}

// Cleans up any pointer variables and frees up allocated memory (no heap frag :p)
void LevelManager::Clean()
{
}


// Initializes all of the scenes that are in the game.
void LevelManager::InitLevelSelectionScreens() {
	m_levelScreens = { // Assigned in order.
		nullptr, // No scene
		new StartScene,
		new SelectScene,
		new TutorialScene, // Tutorial
		new LevelOneScene, // Level 1
		new LevelTwoScene, // Level 2
		new LevelThreeScene, // Level 3
		new BossScene, // Boss Level
		new PlayScene, // Play Scene
		new PauseScene, // Pause Scene
		new GameOverScene, // Game Over Screen
		new EndScene // End Scene
	};
}