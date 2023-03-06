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
	Collision();
	UpdateDisplayList();
	Game::Instance().SetLevelBoundaries({Game::Instance().GetLevelBoundaries().x,Game::Instance().GetLevelBoundaries().y,Game::Instance().GetLevelBoundaries().z+0.25f,Game::Instance().GetLevelBoundaries().w+0.25f});
	Camera::Instance().GetTransform()->position.x = Util::Clamp(Camera::Instance().GetTransform()->position.x,Game::Instance().GetLevelBoundaries().x,Game::Instance().GetLevelBoundaries().y);
	Camera::Instance().GetTransform()->position.y = Util::Clamp(Camera::Instance().GetTransform()->position.y,Game::Instance().GetLevelBoundaries().z,Game::Instance().GetLevelBoundaries().w);

	// Set FPS display on screen.
	if ((SDL_GetTicks64() / 1000) > 0)
	{
		int fps = Game::Instance().GetFrames() / (SDL_GetTicks64() / 1000);
		const std::string fpsText = "FPS: " + std::to_string(fps);
		m_pFpsCounter->SetText(fpsText);
	}
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
		m_torpedoPool->Fire();
		//SoundManager::Instance().PlaySound("playerShoot");
		}
}
void PlayScene::Start()
{
	Camera::Instance().SetEnabled(true);
	Game::Instance().SetDebugMode(true);
	Game::Instance().SetLevelBoundaries({-600.0f,600.0f,-600.0f,600.0f});
	// Set GUI Title
	m_guiTitle = "Play Scene";

	m_pBackground = new Background;
	AddChild(m_pBackground,BACKGROUND);
	// Player Sprite
	m_pPlayer = new Player;
	Game::Instance().SetPlayer(m_pPlayer);
	m_pPlayer->SetIsCentered(true);
	AddChild(m_pPlayer,PLAYERS);
	m_playerFacingRight = true;

	// Instantiating the torpedo pool.
	m_torpedoPool = new TorpedoPool();
	AddChild(m_torpedoPool, PROJECTILES);

	// Spawning a test shark for now
	m_enemyPool = new EnemyPool(); 
	AddChild(m_enemyPool,ENEMIES);

	m_enemyPool->Spawn(new Shark);

	// Instantiating the obstcale pool.
	m_pObstaclePool = new ObstaclePool();
	AddChild(m_pObstaclePool, OBSTACLE);

	auto m_pObstacle = new Obstacle();
	m_pObstacle->GetTransform()->position= {600.0f,600.0f};
	m_pObstaclePool->Spawn(m_pObstacle);

	// FPS Counter Set-Up
	m_pFpsCounter = new Label;
	m_pFpsCounter->SetEnabled(true);
	m_pFpsCounter->SetHeight(50);
	m_pFpsCounter->SetWidth(50);
	m_pFpsCounter->SetText("0 fps");
	m_pFpsCounter->GetTransform()->position = {90.0f,30.0f};
	m_pFpsCounter->SetSize(40);
	m_pFpsCounter->SetColour({255,255,0,255});
	if(!Game::Instance().GetDebugMode())
	{
		m_pFpsCounter->SetVisible(false);
	}
	AddChild(m_pFpsCounter,UI);

	
	/* DO NOT REMOVE */
	ImGuiWindowFrame::Instance().SetGuiFunction([this] { GUI_Function(); });
}

void PlayScene::Collision()
{
	
	for (auto enemy : m_enemyPool->GetPool())
	{
		if(Util::Distance(enemy->GetTransform()->position,m_pPlayer->GetTransform()->position)<50.0f)
		{
			if (CollisionManager::AABBCheck(enemy,m_pPlayer)) 
			{
				std::cout <<  "Enemy player collision" <<::std::endl;
				enemy->GetRigidBody()->isColliding=true;
				m_pPlayer->GetRigidBody()->isColliding=true;
			}
			else
			{
				m_pPlayer->GetRigidBody()->isColliding = false; //probably not good cause there are other things they could be colliding with
			}
		}
		for (auto projectile : m_torpedoPool->GetPool())
		{
			if(projectile->GetProjectileSource()->GetType()== GameObjectType::PLAYER)
			{
				if(Util::Distance(enemy->GetTransform()->position,projectile->GetTransform()->position)<30.0f)
				{
					if (CollisionManager::AABBCheck(enemy,projectile)) 
					{
						std::cout <<  "Bullet enemy collision" <<::std::endl;
						enemy->SetHealth(enemy->GetHealth()-projectile->GetDamage());
						projectile->GetRigidBody()->isColliding=true;
						enemy->GetRigidBody()->isColliding=true;
					}
					else
					{
						projectile->GetRigidBody()->isColliding = false;
					}
				}
			}
		}
		
	}
	for (auto obstacle: m_pObstacles)
	{
		//std::cout << m_pPlayer->GetTransform()->position.x << " , " << m_pPlayer->GetTransform()->position.y <<  std::endl;
		//std::cout << obstacle->GetTransform()->position.x<<" , " <<  obstacle->GetTransform()->position.y <<  std::endl;
		//std::cout << m_pShark->GetTransform()->position.x << " , " << m_pShark->GetTransform()->position.y << std::endl;
			
		if(CollisionManager::AABBCheck(obstacle,m_pPlayer))
		{
		}
		
	}
	
	//only needed in play state, not start or end or pause.
	//each game object type will probably want to use a different type of collision
	//dont want to do object->checkcollision with all objects because then each collision will be checked twice
	//want to use distance checker to be within a certain range before checking collision.
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
