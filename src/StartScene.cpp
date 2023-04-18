#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	//StartScene::Start();
}

StartScene::~StartScene()
= default;

void StartScene::Draw()
{
	DrawDisplayList();
}

void StartScene::Update()
{
	UpdateDisplayList();
}

void StartScene::Clean()
{
	SoundManager::Instance().StopMusic(0.5f);
	RemoveAllChildren();
}

void StartScene::HandleEvents()
{
	EventManager::Instance().Update();

	// Keyboard Events
	if(EventManager::Instance().IsKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance().Quit();
	}
}

void StartScene::Start()
{
	SoundManager::Instance().Load("../Assets/audio/start.mp3", "Start", SoundType::SOUND_MUSIC);
	SoundManager::Instance().PlayMusic("Start");

	ChangeCurrentState(MENU);

	ImGuiWindowFrame::Instance().SetDefaultGuiFunction();
}

// I feel like making a button can be put into a function / label since how many times we call it. Oh well it's 4:00 and winton moment
void StartScene::ChangeCurrentState(START_SCENE_STATE curState)
{
	// Essentially cleaning the scene before we change the state!
	RemoveAllChildren();
	constexpr SDL_Color blue = { 0, 0, 255, 255 };
	constexpr SDL_Color Black = { 255, 255, 255, 255 };
	Label* tempLabel;

	switch (curState)
	{
	case MENU:
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
				if (!mouseAlreadyPressed)
				{
					m_pStartButton->SetActive(false);
					mouseAlreadyPressed = true;
					ChangeCurrentState(ASK_TUTORIAL);
					//SoundManager::Instance().stop_music("Start", 0);
				}
				else {
					mouseAlreadyPressed = false;
				}
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
		m_pInstructionsLabel = new Label("START", "Consolas", 30, Black, m_pStartButton->GetTransform()->position);
		m_pInstructionsLabel->SetParent(this);
		AddChild(m_pInstructionsLabel);

		// Exit button
		m_pExitButton = new Button();
		m_pExitButton->GetTransform()->position = glm::vec2(1280.0f / 2.0f, 500.0f);

		m_pExitButton->AddEventListener(Event::CLICK, [&]()-> void
			{
				if (!mouseAlreadyPressed)
				{
					m_pExitButton->SetActive(false);
					mouseAlreadyPressed = true;
					Game::Instance().Quit();
				}
				else {
					mouseAlreadyPressed = false;
				}
				
			});

		m_pExitButton->AddEventListener(Event::MOUSE_OVER, [&]()->void
			{
				m_pExitButton->SetAlpha(128);
			});

		m_pExitButton->AddEventListener(Event::MOUSE_OUT, [&]()->void
			{
				m_pExitButton->SetAlpha(255);
			});

		AddChild(m_pExitButton);
		m_pExitLabel = new Label("EXIT", "Consolas", 30, Black, m_pExitButton->GetTransform()->position);
		m_pExitLabel->SetParent(this);
		AddChild(m_pExitLabel);
		break;


	case ASK_TUTORIAL:
		tempLabel = new Label("Tutorial?", "Dock51", 60, blue, glm::vec2(1280 / 2, 100));
		tempLabel->SetParent(this);
		AddChild(tempLabel);

		// YesTutorial button
		m_pTutorialButton = new Button();
		m_pTutorialButton->GetTransform()->position = glm::vec2(1280.0f / 2.0f, 300.0f);

		m_pTutorialButton->AddEventListener(Event::CLICK, [&]()-> void
			{
				if (!mouseAlreadyPressed)
				{
					m_pTutorialButton->SetActive(false);
					mouseAlreadyPressed = true;
					Game::Instance().ChangeSceneState(SceneState::TUTORIAL);
				}
				else {
					mouseAlreadyPressed = false;
				}

			});

		m_pTutorialButton->AddEventListener(Event::MOUSE_OVER, [&]()->void
			{
				m_pTutorialButton->SetAlpha(128);
			});

		m_pTutorialButton->AddEventListener(Event::MOUSE_OUT, [&]()->void
			{
				m_pTutorialButton->SetAlpha(255);
			});

		AddChild(m_pTutorialButton);
		m_pTutorialLabel = new Label("YES", "Consolas", 30, Black, m_pTutorialButton->GetTransform()->position);
		m_pTutorialLabel->SetParent(this);
		AddChild(m_pTutorialLabel);

		// NoTutorial Button
		m_pNoTutorialButton = new Button();
		m_pNoTutorialButton->GetTransform()->position = glm::vec2(1280.0f / 2.0f, 400.0f);

		m_pNoTutorialButton->AddEventListener(Event::CLICK, [&]()-> void
			{
				if (!mouseAlreadyPressed)
				{
					m_pNoTutorialButton->SetActive(false);
					mouseAlreadyPressed = true;
					Game::Instance().ChangeSceneState(SceneState::LEVEL_SELECT);
				}
				else {
					mouseAlreadyPressed = false;
				}

			});

		m_pNoTutorialButton->AddEventListener(Event::MOUSE_OVER, [&]()->void
			{
				m_pNoTutorialButton->SetAlpha(128);
			});

		m_pNoTutorialButton->AddEventListener(Event::MOUSE_OUT, [&]()->void
			{
				m_pNoTutorialButton->SetAlpha(255);
			});

		AddChild(m_pNoTutorialButton);
		m_pNoTutorialLabel = new Label("NO", "Consolas", 30, Black, m_pNoTutorialButton->GetTransform()->position);
		m_pNoTutorialLabel->SetParent(this);
		AddChild(m_pNoTutorialLabel);

		// Back Button
		m_pBackButton = new Button();
		m_pBackButton->GetTransform()->position = glm::vec2(1280.0f / 2.0f, 500.0f);

		m_pBackButton->AddEventListener(Event::CLICK, [&]()-> void
			{
				if (!mouseAlreadyPressed)
				{
					m_pNoTutorialButton->SetActive(false);
					mouseAlreadyPressed = true;
					ChangeCurrentState(MENU);
				}
				else {
					mouseAlreadyPressed = false;
				}
				
			});

		m_pBackButton->AddEventListener(Event::MOUSE_OVER, [&]()->void
			{
				m_pBackButton->SetAlpha(128);
			});

		m_pBackButton->AddEventListener(Event::MOUSE_OUT, [&]()->void
			{
				m_pBackButton->SetAlpha(255);
			});

		AddChild(m_pBackButton);
		// THIS WILL NOT WORK FOR WHATEVER REASON HELP
		//m_pBackLabel = new Label("BACK", "Consolas", 30, Black, m_pBackButton->GetTransform()->position);
		//m_pBackLabel->SetParent(this);
		//AddChild(m_pBackLabel);

		break;


	case LOADING:

		break;


	}
}

