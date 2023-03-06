#include "L2Scene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

L2S::L2S()
{
	L2S::Start();
}

L2S::~L2S()
= default;

void L2S::Draw()
{
	DrawDisplayList();
}

void L2S::Update()
{
	UpdateDisplayList();
}

void L2S::Clean()
{
	RemoveAllChildren();
}

void L2S::HandleEvents()
{
	EventManager::Instance().Update();

	// Keyboard Events
	if(EventManager::Instance().IsKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance().Quit();
	}

	if(EventManager::Instance().IsKeyDown(SDL_SCANCODE_P))
	{
		Game::Instance().ChangeSceneState(SceneState::PLAY);
	}
	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_LEFT))
	{
		Game::Instance().ChangeSceneState(SceneState::LS1);
	}
	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_RIGHT))
	{
		Game::Instance().ChangeSceneState(SceneState::LS3);
	}
	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_M))
	{
		Game::Instance().ChangeSceneState(SceneState::START);
	}
}

void L2S::Start()
{
	constexpr SDL_Color blue = { 0, 0, 255, 255 };
	m_pStartLabel = new Label("L2", "Dock51", 80, blue, glm::vec2(1280/2,100));
	m_pStartLabel->SetParent(this);
	AddChild(m_pStartLabel);

	m_pInstructionsLabel = new Label("Click to Shoot. Press SPACE to move.", "Consolas", 40, blue, glm::vec2(1280/2, 720/2-150));
	m_pInstructionsLabel->SetParent(this);
	AddChild(m_pInstructionsLabel);


	
	// Start Button
	m_pStartButton = new Button();
	m_pStartButton->GetTransform()->position = glm::vec2(1280.0f/2.0f, 400.0f); 

	m_pStartButton->AddEventListener(Event::CLICK, [&]()-> void
	{
		m_pStartButton->SetActive(false);
		Game::Instance().ChangeSceneState(SceneState::PLAY);
	});
	
	m_pStartButton->AddEventListener(Event::MOUSE_OVER, [&]()->void
	{
		m_pStartButton->SetAlpha(128);
	});

	m_pStartButton->AddEventListener(Event::MOUSE_OUT, [&]()->void
	{
		m_pStartButton->SetAlpha(255);
	});
	AddChild(m_pStartButton);

	ImGuiWindowFrame::Instance().SetDefaultGuiFunction();
}

