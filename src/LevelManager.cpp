#include "LevelManager.h"

// Static variable initializers :)
std::array<Scene*, static_cast<int>(SceneState::NUM_OF_SCENES)> LevelManager::m_levelScreens;
Scene* LevelManager::m_pCurrentLevel;

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
}

// Renders the current level.
void LevelManager::RenderLevel()
{
	m_pCurrentLevel->Draw();
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
		new PrologueScene, // Prologue
		new LevelOneScene, // Level 1
		new LevelTwoScene, // Level 2
		new LevelThreeScene, // Level 3
		new BossScene, // Boss Level
		new PlayScene, // Play Scene
		new EndScene // End Scene
	};
}