#include "SelectScene.h"

#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"
#include "MenuPlayer.h"
#include "Util.h"
#include "Layers.h"
#include "LevelSelectionObject.h"
#include "LevelManager.h"

SelectScene::SelectScene() : m_player(nullptr)
{
}

SelectScene::~SelectScene()
= default;

void SelectScene::Draw()
{
	DrawDisplayList();
}

void SelectScene::Update()
{
	Game::Instance().SetLevelBoundaries({ Game::Instance().GetLevelBoundaries().x,Game::Instance().GetLevelBoundaries().y,Game::Instance().GetLevelBoundaries().z + 0.25f,Game::Instance().GetLevelBoundaries().w + 0.25f });
	Camera::Instance().GetTransform()->position.x = Util::Clamp(Camera::Instance().GetTransform()->position.x, Game::Instance().GetLevelBoundaries().x, Game::Instance().GetLevelBoundaries().y);
	//Camera::Instance().GetTransform()->position.y = Util::Clamp(Camera::Instance().GetTransform()->position.y, Game::Instance().GetLevelBoundaries().z, Game::Instance().GetLevelBoundaries().w);

	// Obstacle checker if player is in the distance for level swapper to work.
	for (Obstacle* obstacle : m_pObstaclePool->GetPool()) {
		if (obstacle->tag == "LevelSelector") {
			if (Util::Distance(m_player->GetTransform()->position, obstacle->GetTransform()->position) <= 125.0f) {
				static_cast<LevelSelectionObject*>(obstacle)->SetLabel(true);
			}
			else {
				static_cast<LevelSelectionObject*>(obstacle)->SetLabel(false);
			}

		}
	}
	UpdateDisplayList();
}

void SelectScene::Clean()
{
	Camera::Instance().SetEnabled(false);
	RemoveAllChildren();
}

void SelectScene::HandleEvents()
{
	EventManager::Instance().Update();

	// Keyboard Events
	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance().Quit();
	}
	
	// Player movement events
	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_A)) {
		m_player->Move(true);
	}
	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_D)) {
		m_player->Move(false);
	}
	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_E)) {
		for (auto obstacle : m_pObstaclePool->GetPool()) {
			if (static_cast<LevelSelectionObject*>(obstacle)->GetLabel()) { // If label is enabled for the player and we can change scenes
				std::cout << "changing scenes...\n\n";
				Game::Instance().ChangeSceneState(SceneState::LEVEL_ONE);
			}
		}
	}
}

void SelectScene::Start()
{
	m_pBackground = new Background("../Assets/textures/SelectScreen/Select_screen.png", "menuBG");
	m_pBackground->GetTransform()->position={0,-55};
	m_pBackground->SetScale(1.25f);
	AddChild(m_pBackground, BACKGROUND);

	// Adding gameObjects to scene.
	m_player = new MenuPlayer;
	m_player->SetIsCentered(true);
	AddChild(m_player, PLAYERS);

	m_pObstaclePool = new ObstaclePool();
	AddChild(m_pObstaclePool, OBSTACLE);

	Game::Instance().SetDebugMode(true);
	Camera::Instance().SetEnabled(true);

	Game::Instance().SetLevelBoundaries({0, 0,-600.0f, 600.0f});

	InitLevelSelectionObstacles();

	ImGuiWindowFrame::Instance().SetDefaultGuiFunction();
}

void SelectScene::InitLevelSelectionObstacles()
{
	for (int i = 0; i < LEVELS; i++) {
		LevelSelectionObject* temp = new LevelSelectionObject();
		temp->GetTransform()->position = glm::vec2(250 + (400 * i), 500);
		m_pObstaclePool->Spawn(temp);
	}
}

