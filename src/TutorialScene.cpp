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

TutorialScene::TutorialScene() : m_player(nullptr), m_pObstaclePool(nullptr)
{
}

TutorialScene::~TutorialScene()
= default;

void TutorialScene::Draw()
{
	DrawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance().GetRenderer(), 255, 255, 255, 255);
}

void TutorialScene::Update()
{
	Game::Instance().SetLevelBoundaries({ Game::Instance().GetLevelBoundaries().x,Game::Instance().GetLevelBoundaries().y,Game::Instance().GetLevelBoundaries().z + 0.25f,Game::Instance().GetLevelBoundaries().w + 0.25f });
	Camera::Instance().GetTransform()->position.x = Util::Clamp(Camera::Instance().GetTransform()->position.x, Game::Instance().GetLevelBoundaries().x, Game::Instance().GetLevelBoundaries().y);
	Camera::Instance().GetTransform()->position.y = -30;

	// Set position of text to the midpoint of the text bar ALWAYS
	m_pText->GetTransform()->position = { textBar->GetTransform()->position.x * 4.25, textBar->GetTransform()->position.y * 1.5 };

	if (m_isTyping)
	{
		// Add text if timer is beyond the max limit!

		if (timerUntilNextType >= maxTimer) {
			timerUntilNextType = 0.0f;
			stringIterator++;
			std::cout << stringIterator << std::endl;
			if (stringIterator >= current_text.length()) {
				m_isTyping = false;
				std::cout << "false!";
			}
			else {
				std::cout << current_text[stringIterator];
				m_pText->SetText(m_pText->GetText() + std::string(1, current_text[stringIterator]));
			}
		}


		timerUntilNextType += Game::Instance().GetDeltaTime();
	}


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
		SayText("winton");
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
void TutorialScene::SayText(const std::string &textToSay)
{
	// Clear text for the new dialogue
	m_pText->SetText(std::string(1, textToSay[0]));

	current_text = textToSay;
	stringIterator = 0;
	m_isTyping = true;
}

