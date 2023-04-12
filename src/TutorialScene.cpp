#include "TutorialScene.h"

#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"
#include "MenuPlayer.h"
#include "Util.h"
#include "Layers.h"
#include "LevelSelectionObject.h"
#include "LevelManager.h"

TutorialScene::TutorialScene() : m_player(nullptr)
{
}

TutorialScene::~TutorialScene()
= default;

void TutorialScene::Draw()
{
	DrawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance().GetRenderer(), 255, 255, 255, 255);
	if (!m_isTyping)
	{
		// Render the text bar! (maybe this entire text thing can be a class later) ;p
		TextureManager::Instance().DrawScale("textenterBar", m_pText->GetTransform()->scale.x + 5.0f, m_pText->GetTransform()->position.y, 0.25f);
	}
}

void TutorialScene::Update()
{
	Game::Instance().SetLevelBoundaries({ Game::Instance().GetLevelBoundaries().x,Game::Instance().GetLevelBoundaries().y,Game::Instance().GetLevelBoundaries().z + 0.25f,Game::Instance().GetLevelBoundaries().w + 0.25f });
	Camera::Instance().GetTransform()->position.x = Util::Clamp(Camera::Instance().GetTransform()->position.x, Game::Instance().GetLevelBoundaries().x, Game::Instance().GetLevelBoundaries().y);
	Camera::Instance().GetTransform()->position.y = -30;

	// Set position of text to the midpoint of the text bar ALWAYS
	m_pText->GetTransform()->position = { textBar->GetTransform()->position.x * 4.25, textBar->GetTransform()->position.y * 1.5 };

	UpdateDisplayList();
}

void TutorialScene::Clean()
{
	Camera::Instance().SetEnabled(false);
	RemoveAllChildren();

	
}

void TutorialScene::HandleEvents()
{
	EventManager::Instance().Update();

	// Keyboard Events
	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance().Quit();
	}
	
	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_F)) {
		SayText("hi im winton");
	}
	if (!m_isInCutscene)
	{
		// Player movement events if we are not in a cutscene.
	}
	
}

void TutorialScene::Start()
{
	SoundManager::Instance().SetMusicVolume(2);
	SoundManager::Instance().Load("../Assets/audio/LevelMusic/SelectScreen/boop.mp3", "Radio", SoundType::SOUND_MUSIC);
	SoundManager::Instance().PlayMusic("Radio", -1);

	TextureManager::Instance().Load("../Assets/sprites/textbox/TextEnterBar.png", "textenterBar");

	m_pBackground = new Background("../Assets/textures/SelectScreen/select_screen_wide.png", "tutorialScreen");
	m_pBackground->GetTransform()->position={0, -30};
	//m_pBackground->SetScale(1.25f);
	AddChild(m_pBackground, BACKGROUND);

	textBar = new Background("../Assets/sprites/textbox/textBox.png", "textbox");
	textBar->GetTransform()->position = { 150, 350 };
	textBar->SetScale(0.75f);
	AddChild(textBar);

	m_pText = new Label("winton time!!!11!!", "Consolas", 24);
	m_pText->SetParent(this);
	m_pText->GetTransform()->position = { textBar->GetTransform()->position.x * 4.25, textBar->GetTransform()->position.y * 1.5};
	AddChild(m_pText);

	m_pObstaclePool = new ObstaclePool();
	AddChild(m_pObstaclePool, OBSTACLE);

	Game::Instance().SetDebugMode(false);
	Camera::Instance().SetEnabled(true);

	Game::Instance().SetLevelBoundaries({0, 0,-600.0f, 600.0f});

	Obstacle* temp = new Obstacle("radio", "../Assets/sprites/decorations/radio_larger.png");
	temp->GetTransform()->position = glm::vec2(1200, 465);
	m_pObstaclePool->Spawn(temp);


	ImGuiWindowFrame::Instance().SetDefaultGuiFunction();
}

// Speaks text character by character, although rn since it is in a while loop it does not draw properly -_-
void TutorialScene::SayText(std::string textToSay)
{
	float timer = 0;
	float maxTimer = 1.0f;
	// Clear text for the new dialogue
	m_isTyping = true;
	m_pText->SetText(" ");

	bool currentChar = false;

	for (char character : textToSay)
	{
		timer = 0;
		currentChar = true;
		while (currentChar)
		{
			if (timer >= maxTimer) {
				m_pText->SetText(m_pText->GetText() + character);
				currentChar = false;
			}
			std::cout << timer << std::endl;
			timer += Game::Instance().GetDeltaTime();
		}		
	}
	m_isTyping = false;
}

