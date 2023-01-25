#include "EndScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"
#include "WorldManager.h"

EndScene::EndScene()
{
	EndScene::Start();
}

EndScene::~EndScene()
= default;

void EndScene::Draw()
{
	DrawDisplayList();
}

void EndScene::Update()
{
	UpdateDisplayList();
}

void EndScene::Clean()
{
	RemoveAllChildren();
}

void EndScene::HandleEvents()
{
	EventManager::Instance().Update();

	// Button Events
	m_pRestartButton->Update();

	// Keyboard Events
	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance().Quit();
	}

	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_1))
	{
		Game::Instance().ChangeSceneState(SceneState::PLAY);
	}
}

void EndScene::Start()
{
	const SDL_Color blue = { 0, 0, 255, 255 };
	m_label = new Label("END SCENE", "Dock51", 80, blue, b2Vec2(400.0f, 40.0f));
	m_label->SetParent(this);
	AddChild(m_label);

	// Restart Button
	m_pRestartButton = new Button("../Assets/textures/restartButton.png", "restartButton", GameObjectType::RESTART_BUTTON);
	m_pRestartButton->InitRigidBody();
	m_pRestartButton->AddEventListener(Event::CLICK, [&]()-> void
	{
		m_pRestartButton->SetActive(false);
		Game::Instance().ChangeSceneState(SceneState::PLAY);
	});

	m_pRestartButton->AddEventListener(Event::MOUSE_OVER, [&]()->void
	{
		m_pRestartButton->SetAlpha(128);
	});

	m_pRestartButton->AddEventListener(Event::MOUSE_OUT, [&]()->void
	{
		m_pRestartButton->SetAlpha(255);
	});

	AddChild(m_pRestartButton);

	ImGuiWindowFrame::Instance().SetDefaultGuiFunction();
}
void EndScene::InitRigidBody()
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(0.0f, 0.0f);
	bodyDef.enabled = true;
	bodyDef.type = b2_kinematicBody;
	m_rigidBody = WorldManager::Instance().GetWorld()->CreateBody(&bodyDef);
}
b2Body* EndScene::GetRigidBody()
{
	return m_rigidBody;
}