#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::Start();
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

	if(EventManager::Instance().IsKeyDown(SDL_SCANCODE_1))
	{
		Game::Instance().ChangeSceneState(SceneState::PLAY);
	}
}

void StartScene::Start()
{
	const SDL_Color blue = { 0, 0, 255, 255 };
	m_pStartLabel = new Label("START SCENE", "Consolas", 80, blue, b2Vec2(400.0f, 40.0f));
	m_pStartLabel->InitRigidBody(b2Vec2(400.0f,40.0f));
	m_pStartLabel->SetParent(this);
	AddChild(m_pStartLabel);

	m_pInstructionsLabel = new Label("Press 1 to Play", "Consolas", 40, blue, b2Vec2(400.0f, 120.0f));
	m_pInstructionsLabel->InitRigidBody(b2Vec2(400.0f,120.0f));
	m_pInstructionsLabel->SetParent(this);
	AddChild(m_pInstructionsLabel);

	InitRigidBody(b2Vec2(0.0f,0.0f));

	// Start Button
	m_pStartButton = new Button();
	m_pStartButton->InitRigidBody(b2Vec2(400.0f,400.0f));
	

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

}
void StartScene::InitRigidBody(b2Vec2 position)
{
	bodyDef.position.Set(position.x, position.y);
	m_rigidBody = Game::Instance().world->CreateBody(&bodyDef);
}
b2Body* StartScene::GetRigidBody()
{
	return m_rigidBody;
}
