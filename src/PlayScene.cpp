#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"
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
	m_angle = (atan2((m_pPlayer->GetRigidBody()->GetPosition().y - Game::Instance().GetMousePosition().y) - Game::Instance().camera.y, (m_pPlayer->GetRigidBody()->GetPosition().x - Game::Instance().GetMousePosition().x) - Game::Instance().camera.x));
	Game::Instance().camera.x = (m_pPlayer->GetRigidBody()->GetPosition().x + m_pPlayer->GetWidth() / 2) - m_ScreenWidth / 2;
	Game::Instance().camera.y = (m_pPlayer->GetRigidBody()->GetPosition().y + m_pPlayer->GetHeight() / 2) - m_ScreenHeight / 2;
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
		if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_A))
		{
			m_pPlayer->SetAnimationState(PlayerAnimationState::PLAYER_RUN_LEFT);
			//m_pPlayer->GetRigidBody()->GetLinearVelocity() -= b2Vec2(m_pPlayer->m_speed, 0.0f);
			m_playerFacingRight = false;
		}
		else if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_D))
		{
			m_pPlayer->SetAnimationState(PlayerAnimationState::PLAYER_RUN_RIGHT);
			//m_pPlayer->GetRigidBody()->GetLinearVelocity() += b2Vec2(m_pPlayer->m_speed, 0.0f);
			m_playerFacingRight = true;
		}
		else
		{
			if (m_playerFacingRight)
			{
				m_pPlayer->SetAnimationState(PlayerAnimationState::PLAYER_IDLE_RIGHT);
			}
			else
			{
				m_pPlayer->SetAnimationState(PlayerAnimationState::PLAYER_IDLE_LEFT);
			}
		}
		if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_W))
		{
			//m_pPlayer->GetRigidBody()->GetLinearVelocity() -= b2Vec2(0.0f, m_pPlayer->m_speed);
		}
		else if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_S))
		{
			//m_pPlayer->GetRigidBody()->GetLinearVelocity() += b2Vec2(0.0f, m_pPlayer->m_speed);
		}
		if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_SPACE))
		{
			//m_pPlayer->GetRigidBody()->GetLinearVelocity() = b2Vec2(-cos(m_angle)*2.5f, -sin(m_angle)*2.5f);
		}
	}
	if(EventManager::Instance().MousePressed(1))
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
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(0.0f, 0.0f);
	bodyDef.enabled = true;
	m_rigidBody = Game::Instance().world->CreateBody(&bodyDef);
}
