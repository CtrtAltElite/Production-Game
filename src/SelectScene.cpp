#include "SelectScene.h"

#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"
#include "MenuPlayer.h"
#include "Util.h"
#include "Layers.h"

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

	UpdateDisplayList();
}

void SelectScene::Clean()
{
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
}

void SelectScene::Start()
{
	m_pBackground = new Background("../Assets/textures/MenuBackground.png", "menuBG");
	AddChild(m_pBackground, BACKGROUND);


	m_player = new MenuPlayer;
	m_player->SetIsCentered(true);
	AddChild(m_player, PLAYERS);
	Game::Instance().SetDebugMode(true);
	Camera::Instance().SetEnabled(true);

	Game::Instance().SetLevelBoundaries({-200, 500,-600.0f, 600.0f});

	ImGuiWindowFrame::Instance().SetDefaultGuiFunction();
}

