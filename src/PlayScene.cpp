#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "Camera.h"
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"
#include "WorldManager.h"

PlayScene::PlayScene()
{
	PlayScene::Start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::Draw()
{
	DrawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance().GetRenderer(), 255, 255, 255, 255);
}

void PlayScene::Update()
{
	UpdateDisplayList();
	m_angle = (atan2((m_pPlayer->GetRigidBody()->GetPosition().y - Game::Instance().GetMousePosition().y) - Camera::Instance().GetPosition().y, (m_pPlayer->GetRigidBody()->GetPosition().x - Game::Instance().GetMousePosition().x) - Camera::Instance().GetPosition().x));
	//b2Vec2 camPos = { (m_pPlayer->GetRigidBody()->GetPosition().x + m_pPlayer->GetWidth() / 2) - m_ScreenWidth / 2 ,(m_pPlayer->GetRigidBody()->GetPosition().y + m_pPlayer->GetHeight() / 2) - m_ScreenHeight / 2 };
	b2Vec2 camPos = { 0.0,0.0 };
	Camera::Instance().SetPosition(camPos);
}

void PlayScene::Clean()
{
	RemoveAllChildren();
}

void PlayScene::HandleEvents()
{
	EventManager::Instance().Update();



	// handle player movement if no Game Controllers found
	if (SDL_NumJoysticks() < 1)
		//CHANGE TO BOX2D PHYSICS 
	{
		if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_SPACE))
		{
			m_pPlayer->MoveAtMouse();
		}
	}
	if(EventManager::Instance().MousePressed(1)) //left mouse button
	{
		m_pProjectile = new Projectile(m_pPlayer);
		AddChild(m_pProjectile);
		m_pProjVec.push_back(m_pProjectile);
	}

	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance().Quit();
	}

	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_1))
	{
		Game::Instance().ChangeSceneState(SceneState::START);
	}

	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_2))
	{
		Game::Instance().ChangeSceneState(SceneState::END);
	}
}

void PlayScene::Start()
{

	InitRigidBody();
	// Player Sprite
	m_pBackground = new Background();
	AddChild(m_pBackground);
	m_pPlayer = new Player();
	AddChild(m_pPlayer);
	m_playerFacingRight = true;

	


}
void PlayScene::InitRigidBody()
{
	m_rigidBody = WorldManager::Instance().CreateRigidBody({ 0.0f,0.0f });
}
b2Body* PlayScene::GetRigidBody()
{
	return m_rigidBody;
}