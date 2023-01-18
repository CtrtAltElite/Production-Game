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
	SDL_GetMouseState(&m_mouseX, &m_mouseY);
	m_angle = (atan2((m_pPlayer->GetTransform()->position.y - m_mouseY) - Game::Instance().camera.y, (m_pPlayer->GetTransform()->position.x - m_mouseX) - Game::Instance().camera.x));
	Game::Instance().camera.x = (m_pPlayer->GetTransform()->position.x + m_pPlayer->GetWidth() / 2) - m_ScreenWidth / 2;
	Game::Instance().camera.y = (m_pPlayer->GetTransform()->position.y + m_pPlayer->GetHeight() / 2) - m_ScreenHeight / 2;
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
	{
		if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_A))
		{
			m_pPlayer->SetAnimationState(PlayerAnimationState::PLAYER_RUN_LEFT);
			//m_pPlayer->GetTransform()->position -= glm::vec2(5.0f,0.0f);
			m_pPlayer->GetRigidBody()->velocity -= glm::vec2(m_pPlayer->m_speed, 0.0f);
			m_playerFacingRight = false;
		}
		else if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_D))
		{
			m_pPlayer->SetAnimationState(PlayerAnimationState::PLAYER_RUN_RIGHT);
			//m_pPlayer->GetTransform()->position += glm::vec2(5.0f, 0.0f);
			m_pPlayer->GetRigidBody()->velocity += glm::vec2(m_pPlayer->m_speed, 0.0f);
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
			m_pPlayer->GetRigidBody()->velocity -= glm::vec2(0.0f, m_pPlayer->m_speed);
		}
		else if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_S))
		{
			//m_pPlayer->GetTransform()->position += glm::vec2(0.0f, 5.0f);
			m_pPlayer->GetRigidBody()->velocity += glm::vec2(0.0f, m_pPlayer->m_speed);
		}
		if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_SPACE))
		{
			m_pPlayer->GetRigidBody()->velocity = glm::vec2(-cos(m_angle)*2.5f, -sin(m_angle)*2.5f);
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
	// Set GUI Title
	m_guiTitle = "Play Scene";
	m_ScreenHeight = 720;
	m_ScreenWidth = 1280;
	// Player Sprite
	m_pBackground = new Background();
	AddChild(m_pBackground);
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
