#include "PauseScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"
#include "LevelManager.h"
#include "Renderer.h"

PauseScene::PauseScene()
{

}

PauseScene::~PauseScene()
= default;

void PauseScene::Draw()
{
	DrawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance().GetRenderer(), 255, 255, 255, 128);
}

void PauseScene::Update()
{
	UpdateDisplayList();
}

void PauseScene::Clean()
{
	SoundManager::Instance().StopMusic(0.5f);
	RemoveAllChildren();
}

void PauseScene::HandleEvents()
{
	EventManager::Instance().Update();

	// Keyboard Events
	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance().Quit();
	}
}

void PauseScene::Start()
{
	SoundManager::Instance().SetMusicVolume(10);
	//SoundManager::Instance().Load("../Assets/audio/LevelMusic/PauseScreen/Bossa_Nova.mp3", "Pause", SoundType::SOUND_MUSIC);
	//SoundManager::Instance().PlayMusic("Pause", -1, 3000);

	constexpr SDL_Color blue = { 0, 0, 255, 255 };
	constexpr SDL_Color Black = { 255, 255, 255, 255 };
	m_pStartLabel = new Label("PAUSED", "Dock51", 80, blue, glm::vec2(1280 / 2, 100));
	m_pStartLabel->SetParent(this);
	AddChild(m_pStartLabel);

	m_pInstructionsLabel = new Label("Your currently paused.", "Consolas", 40, blue, glm::vec2(1280 / 2, 720 / 2 - 150));
	m_pInstructionsLabel->SetParent(this);
	AddChild(m_pInstructionsLabel);




	// Start Button
	m_pStartButton = new Button();
	m_pStartButton->GetTransform()->position = glm::vec2(1280.0f / 2.0f, 400.0f);

	// We are clicking the Resume button.
	m_pStartButton->AddEventListener(Event::CLICK, [&]()-> void
		{
			SoundManager::Instance().SetMusicVolume(25);
			m_pStartButton->SetActive(false);
			LevelManager::SetPause(false);
			//SoundManager::Instance().stop_music("Start", 0);
		});

	// Hovering over the Resume Button
	m_pStartButton->AddEventListener(Event::MOUSE_OVER, [&]()->void
		{
			m_pStartButton->SetAlpha(128);
		});

	// Not hovering over the Resume button.
	m_pStartButton->AddEventListener(Event::MOUSE_OUT, [&]()->void
		{
			m_pStartButton->SetAlpha(255);
		});
	AddChild(m_pStartButton);
	m_pInstructionsLabel = new Label("RESUME", "Consolas", 30, Black, glm::vec2(1280.0f / 2.0f, 400.0f));
	m_pInstructionsLabel->SetParent(this);
	AddChild(m_pInstructionsLabel);

	ImGuiWindowFrame::Instance().SetDefaultGuiFunction();
}

