#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"
float decay = 0.5f;
float speed = 1.0f;
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
}

void PlayScene::Clean()
{
	RemoveAllChildren();
}

void PlayScene::HandleEvents()
{
	EventManager::Instance().Update();

	// handle player movement with GameController


	// handle player movement if no Game Controllers found
	if (SDL_NumJoysticks() < 1)
	{
		if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_A))
		{
			m_pPlayer->SetAnimationState(PlayerAnimationState::PLAYER_RUN_LEFT);
			//m_pPlayer->GetTransform()->position -= glm::vec2(5.0f,0.0f);
			m_pPlayer->GetRigidBody()->velocity -= glm::vec2(speed, 0.0f);
			m_playerFacingRight = false;
		}
		else if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_D))
		{
			m_pPlayer->SetAnimationState(PlayerAnimationState::PLAYER_RUN_RIGHT);
			//m_pPlayer->GetTransform()->position += glm::vec2(5.0f, 0.0f);
			m_pPlayer->GetRigidBody()->velocity += glm::vec2(speed, 0.0f);
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
			//m_pPlayer->GetTransform()->position -= glm::vec2(0.0f, 5.0f);
			m_pPlayer->GetRigidBody()->velocity -= glm::vec2(0.0f, speed);
		}
		else if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_S))
		{
			//m_pPlayer->GetTransform()->position += glm::vec2(0.0f, 5.0f);
			m_pPlayer->GetRigidBody()->velocity += glm::vec2(0.0f, speed);
		}
	}

	m_pPlayer->GetTransform()->position += m_pPlayer->GetRigidBody()->velocity;
	if (m_pPlayer->GetRigidBody()->velocity.x != 0.0f)
	{
		if (m_pPlayer->GetRigidBody()->velocity.x > 0.0f)
		{
			m_pPlayer->GetRigidBody()->velocity.x -= decay;
		}
		else
		{
			m_pPlayer->GetRigidBody()->velocity.x += decay;
		}
	}
	if (m_pPlayer->GetRigidBody()->velocity.y != 0.0f)
	{
		if (m_pPlayer->GetRigidBody()->velocity.y > 0.0f)
		{
			m_pPlayer->GetRigidBody()->velocity.y -= decay;
		}
		else
		{
			m_pPlayer->GetRigidBody()->velocity.y += decay;
		}
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
	// Set GUI Title
	m_guiTitle = "Play Scene";


	// Player Sprite
	m_pPlayer = new Player();
	AddChild(m_pPlayer);
	m_playerFacingRight = true;


	ImGuiWindowFrame::Instance().SetGuiFunction(std::bind(&PlayScene::GUI_Function, this));
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);


	static float float2[3] = {m_pPlayer->GetTransform()->position.x,m_pPlayer->GetTransform()->position.y};
	if(ImGui::SliderFloat2("Player position", float2, 0.0f, 800.0f))
	{
		if(m_pPlayer->GetTransform()->position.x<float2[0])
		{
			m_pPlayer->SetAnimationState(PlayerAnimationState::PLAYER_RUN_LEFT);
		}
		if (m_pPlayer->GetTransform()->position.x > float2[0])
		{
			m_pPlayer->SetAnimationState(PlayerAnimationState::PLAYER_RUN_RIGHT);
		}
		m_pPlayer->GetTransform()->position = glm::vec2(float2[0], float2[1]);
	}
	
	ImGui::End();
}
