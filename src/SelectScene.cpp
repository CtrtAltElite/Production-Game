#include "SelectScene.h"

#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"
#include "MenuPlayer.h"

SelectScene::SelectScene()
{
	SelectScene::Start();
}

SelectScene::~SelectScene()
= default;

void SelectScene::Draw()
{
	DrawDisplayList();
}

void SelectScene::Update()
{
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
}

void SelectScene::Start()
{
	m_player = new MenuPlayer;
	AddChild(m_player);

	ImGuiWindowFrame::Instance().SetDefaultGuiFunction();
}

