#include "SelectScene.h"

#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

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
	SoundManager::Instance().Load("../Assets/audio/start.mp3", "Start", SoundType::SOUND_MUSIC);
	SoundManager::Instance().PlayMusic("Start", 0);

	constexpr SDL_Color blue = { 0, 0, 255, 255 };
	constexpr SDL_Color Black = { 255, 255, 255, 255 };
	m_pStartLabel = new Label("Project CARL", "Dock51", 80, blue, glm::vec2(1280 / 2, 100));
	m_pStartLabel->SetParent(this);
	AddChild(m_pStartLabel);

	m_pInstructionsLabel = new Label("Click to Shoot. Press SPACE to move.", "Consolas", 40, blue, glm::vec2(1280 / 2, 720 / 2 - 150));
	m_pInstructionsLabel->SetParent(this);
	AddChild(m_pInstructionsLabel);




	// Start Button
	m_pStartButton = new Button();
	m_pStartButton->GetTransform()->position = glm::vec2(1280.0f / 2.0f, 400.0f);

	m_pStartButton->AddEventListener(Event::CLICK, [&]()-> void
		{
			m_pStartButton->SetActive(false);
			Game::Instance().ChangeSceneState(SceneState::LEVEL_SELECT);
			SoundManager::Instance().stop_music("Start", 0);
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
	m_pInstructionsLabel = new Label("START", "Consolas", 30, Black, glm::vec2(1280.0f / 2.0f, 400.0f));
	m_pInstructionsLabel->SetParent(this);
	AddChild(m_pInstructionsLabel);

	ImGuiWindowFrame::Instance().SetDefaultGuiFunction();
}

