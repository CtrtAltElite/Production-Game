#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "InputType.h"

// required for IMGUI
#include "Camera.h"
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Torpedo.h"
#include "Util.h"
#include "Layers.h"

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

	GetPlayerInput();
	
}

void PlayScene::GetPlayerInput()
{
	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_SPACE))
	{
		m_pPlayer->MoveAtMouse();
	}
	if(EventManager::Instance().MousePressed(1)) //left mouse button
		{
		m_pProjectile = new Torpedo(m_pPlayer);
		AddChild(m_pProjectile);
		m_ProjVec.push_back(m_pProjectile);
		//SoundManager::Instance().PlaySound("playerShoot");
		}
}



void PlayScene::Start()
{
	Camera::Instance().SetEnabled(false);
	// Set GUI Title
	m_guiTitle = "Play Scene";

	m_pBackground = new Background();
	AddChild(m_pBackground);
	// Player Sprite
	m_pPlayer = new Player();
	AddChild(m_pPlayer);
	m_playerFacingRight = true;

	m_pShark = new Shark();
	AddChild(m_pShark);
	

	/* DO NOT REMOVE */
	ImGuiWindowFrame::Instance().SetGuiFunction([this] { GUI_Function(); });
}

void PlayScene::GUI_Function() 
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Your Window Title Goes Here", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	ImGui::Text("Player Input");
	ImGui::RadioButton("Keyboard / Mouse", &m_pCurrentInputType, static_cast<int>(InputType::KEYBOARD_MOUSE)); ImGui::SameLine();
	ImGui::RadioButton("Game Controller", &m_pCurrentInputType, static_cast<int>(InputType::GAME_CONTROLLER)); ImGui::SameLine();
	ImGui::RadioButton("Both", &m_pCurrentInputType, static_cast<int>(InputType::ALL));

	ImGui::Separator();

	if(ImGui::Button("My Button"))
	{
		std::cout << "My Button Pressed" << std::endl;
	}

	ImGui::Separator();

	static float float3[3] = { 0.0f, 1.0f, 1.5f };
	if(ImGui::SliderFloat3("My Slider", float3, 0.0f, 2.0f))
	{
		std::cout << float3[0] << std::endl;
		std::cout << float3[1] << std::endl;
		std::cout << float3[2] << std::endl;
		std::cout << "---------------------------\n";
	}
	
	ImGui::End();
}
