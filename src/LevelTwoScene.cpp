#include "LevelTwoScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

LevelTwoScene::LevelTwoScene()
{
}

LevelTwoScene::~LevelTwoScene()
= default;

void LevelTwoScene::Draw()
{
	DrawDisplayList();
}

void LevelTwoScene::Update()
{
	UpdateDisplayList();
}

void LevelTwoScene::Clean()
{
	RemoveAllChildren();
}

void LevelTwoScene::HandleEvents()
{
	EventManager::Instance().Update();

	// Keyboard Events
	if(EventManager::Instance().IsKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance().Quit();
	}
}

void LevelTwoScene::Start()
{
	SoundManager::Instance().Load("../Assets/audio/l2.mp3", "l2", SoundType::SOUND_MUSIC);
	SoundManager::Instance().PlayMusic("l2", 0);
	constexpr SDL_Color blue = { 0, 0, 255, 255 };
	constexpr SDL_Color Black = { 255, 255, 255, 255 };
	m_pStartLabel = new Label("Level 2", "Dock51", 80, blue, glm::vec2(1280/2,100));
	m_pStartLabel->SetParent(this);
	AddChild(m_pStartLabel);

	m_pInstructionsLabel = new Label("Wait? What are you doing...?", "Consolas", 40, blue, glm::vec2(1280/2, 720/2-150));
	m_pInstructionsLabel->SetParent(this);
	AddChild(m_pInstructionsLabel);


	
	/* Start Button
	m_pStartButton = new Button();
	m_pStartButton->GetTransform()->position = glm::vec2(1280.0f/2.0f, 400.0f); 

	m_pStartButton->AddEventListener(Event::CLICK, [&]()-> void
	{
		m_pStartButton->SetActive(false);
		Game::Instance().ChangeSceneState(SceneState::PLAY);
		SoundManager::Instance().stop_music("l2", 0);
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

	 Next Button
	m_pNextButton = new Button();
	m_pNextButton->GetTransform()->position = glm::vec2(1680.0f / 2.0f, 400.0f);

	m_pNextButton->AddEventListener(Event::CLICK, [&]()-> void
		{
			m_pNextButton->SetActive(false);
			Game::Instance().ChangeSceneState(SceneState::LS3);
			SoundManager::Instance().stop_music("l2", 0);
		});

	m_pNextButton->AddEventListener(Event::MOUSE_OVER, [&]()->void
		{
			m_pNextButton->SetAlpha(128);
		});

	m_pNextButton->AddEventListener(Event::MOUSE_OUT, [&]()->void
		{
			m_pNextButton->SetAlpha(255);
		});
	AddChild(m_pNextButton);


	 Prev Button
	m_pPrevButton = new Button();
	m_pPrevButton->GetTransform()->position = glm::vec2(900.0f / 2.0f, 400.0f);

	m_pPrevButton->AddEventListener(Event::CLICK, [&]()-> void
		{
			m_pPrevButton->SetActive(false);
			Game::Instance().ChangeSceneState(SceneState::LS1);
			SoundManager::Instance().stop_music("l2", 0);
		});

	m_pPrevButton->AddEventListener(Event::MOUSE_OVER, [&]()->void
		{
			m_pPrevButton->SetAlpha(128);
		});

	m_pPrevButton->AddEventListener(Event::MOUSE_OUT, [&]()->void
		{
			m_pPrevButton->SetAlpha(255);
		});
	AddChild(m_pPrevButton);

	m_pInstructionsLabel = new Label("PLAY", "Consolas", 30, Black, glm::vec2(1280.0f / 2.0f, 400.0f));
	m_pInstructionsLabel->SetParent(this);
	AddChild(m_pInstructionsLabel);

	m_pInstructionsLabel = new Label("NEXT", "Consolas", 30, Black, glm::vec2(1680.0f / 2.0f, 400.0f));
	m_pInstructionsLabel->SetParent(this);
	AddChild(m_pInstructionsLabel);

	m_pInstructionsLabel = new Label("BACK", "Consolas", 30, Black, glm::vec2(900.0f / 2.0f, 400.0f));
	m_pInstructionsLabel->SetParent(this);
	AddChild(m_pInstructionsLabel);*/

	ImGuiWindowFrame::Instance().SetDefaultGuiFunction();
}

