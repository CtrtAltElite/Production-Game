#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "InputType.h"

// required for IMGUI
#include "Camera.h"
#include "imgui.h"
#include "imgui_sdl.h"
#include "Jellyfish.h"
#include "Renderer.h"
#include "Torpedo.h"
#include "Util.h"
#include "Layers.h"
#include "Stingray.h"

PlayScene::PlayScene()
{
	//PlayScene::Start();
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
	Game::Instance().SetDebugMode(false);
		Collision();
	UpdateDisplayList();
	Game::Instance().SetLevelBoundaries({Game::Instance().GetLevelBoundaries().x,Game::Instance().GetLevelBoundaries().y,Game::Instance().GetLevelBoundaries().z+0.25f,Game::Instance().GetLevelBoundaries().w+0.25f});
	Camera::Instance().GetTransform()->position.x = Util::Clamp(Camera::Instance().GetTransform()->position.x,Game::Instance().GetLevelBoundaries().x,Game::Instance().GetLevelBoundaries().y);
	Camera::Instance().GetTransform()->position.y = Util::Clamp(Camera::Instance().GetTransform()->position.y,Game::Instance().GetLevelBoundaries().z,Game::Instance().GetLevelBoundaries().w);

	if (m_pEnemyPool != nullptr)
	{
		m_pEnemyPool->Update();
	}
	if (m_pObstaclePool != nullptr) {
		m_pObstaclePool->Update();
	}

	//if (timer <= 0)
	//{
	//	timer = NEXT_ENEMY_SPAWN;
	//	auto shark = new Shark;
	//	shark->SetTargetPlayer(m_pPlayer);
	//	m_pEnemyPool->Spawn(shark);

	//	auto stingray = new Stingray;
	//	stingray->GetTransform()->position = glm::vec2(Camera::Instance().GetTransform()->position.x, rand() % 5 + m_pPlayer->GetTransform()->position.y);
	//	m_pObstaclePool->Spawn(stingray);

	//	auto jellyfish = new Jellyfish;
	//	jellyfish->GetTransform()->position = glm::vec2(m_pPlayer->GetTransform()->position.x, m_pPlayer->GetTransform()->position.y - 800.0f);
	//	m_pObstaclePool->Spawn(jellyfish);
	//	//m_pEnemyPool->UpdateTargetPlayer(m_pPlayer);
	//}


	// Set FPS display on screen.
	if ((SDL_GetTicks64() / 1000) > 0)
	{
		const Uint64 fps = Game::Instance().GetFrames() / (SDL_GetTicks64() / 1000);
		const std::string fpsText = "FPS: " + std::to_string(fps);
		m_pFpsCounter->SetText(fpsText);
	}
	timer -= 0.1f;
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

Obstacle* PlayScene::CheckWhatObstacleToSpawn(std::string name)
{
	// Bleh, I dislike string literals for this, really does not help.
	// If jellyfish
	if (name == "JellyFish")
	{
		return new Jellyfish();
	}
	// If sea urchin
	if (name == "SeaUrchin")
	{
		return new SeaUrchin();
	}
	// If pufferfish
	if (name == "Pufferfish")
	{
		return new Pufferfish();
	}
	// If stingray
	if (name == "StingRay")
	{
		return new Stingray();
	}
	// If landfish
	if (name == "LandFish")
	{
		return new LandFish();
	}
	if (m_pTotalObstacles.size() != 1)
	{
		return m_pTotalObstacles[name];
	}
	else {
		return nullptr;
	}
}

void PlayScene::GetPlayerInput()
{
	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_SPACE))
	{
		m_pPlayer->MoveAtMouse();
	}
	if(EventManager::Instance().MousePressed(1)) //left mouse button
		{
		m_pTorpedoPool->Fire();
		//SoundManager::Instance().PlaySound("playerShoot"); //ITS SO LOUD LOL
		}
}

void PlayScene::Start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";


	
	/* DO NOT REMOVE */
	ImGuiWindowFrame::Instance().SetGuiFunction([this] { GUI_Function(); });
}

void PlayScene::Collision()
{
	//there is a better way to do this
	//we need each rigid body to have a vector of collisions anyway to be able to collide with multiple objects (i think)
	//we could use something like this to build the vectors
	//then iterate, manage and do actions with the information fomr the vectors in the objects own updates

	for (auto enemy : m_pEnemyPool->GetPool())
	{
		if (Util::Distance(enemy->GetTransform()->position, m_pPlayer->GetTransform()->position) < 100.0f)
		{
			if (CollisionManager::AABBCheck(enemy, m_pPlayer))
			{
				std::cout << "Enemy player collision" << ::std::endl;
				enemy->GetRigidBody()->isColliding = true;
				enemy->GetRigidBody()->currentCollisions.push_back(m_pPlayer->GetRigidBody());
				m_pPlayer->GetRigidBody()->isColliding = true;
				m_pPlayer->GetRigidBody()->currentCollisions.push_back(enemy->GetRigidBody());
				m_pPlayer->TakeDamage(enemy->GetAttackDamage());
				//make vector of current collisions and pass enemy and m_pPlayer in. so we can have multiple collisions at the same time and access damage values
				//Game::Instance().ChangeSceneState(SceneState::END);
			}
			else
			{
				m_pPlayer->GetRigidBody()->currentCollisions.erase(std::remove(m_pPlayer->GetRigidBody()->currentCollisions.begin(), m_pPlayer->GetRigidBody()->currentCollisions.end(), m_pPlayer->GetRigidBody()),
					m_pPlayer->GetRigidBody()->currentCollisions.end());
				enemy->GetRigidBody()->currentCollisions.erase(std::remove(enemy->GetRigidBody()->currentCollisions.begin(), enemy->GetRigidBody()->currentCollisions.end(), enemy->GetRigidBody()),
					enemy->GetRigidBody()->currentCollisions.end());

				if (m_pPlayer->GetRigidBody()->currentCollisions.empty())
				{
					m_pPlayer->GetRigidBody()->isColliding = false;
				}
				if (enemy->GetRigidBody()->currentCollisions.empty())
				{
					enemy->GetRigidBody()->isColliding = false;
				}
			}
		}
		for (auto projectile : m_pTorpedoPool->GetPool())
		{
			if (projectile->GetProjectileSource()->GetType() == GameObjectType::PLAYER)
			{
				if (Util::Distance(enemy->GetTransform()->position, projectile->GetTransform()->position) < 30.0f)
				{
					if (CollisionManager::AABBCheck(enemy, projectile) || CollisionManager::AABBCheck(projectile, enemy))
					{
						std::cout << "Bullet enemy collision" << ::std::endl;
						enemy->TakeDamage(projectile->GetDamage());
						projectile->GetRigidBody()->isColliding = true;
						enemy->GetRigidBody()->isColliding = true;
						projectile->GetRigidBody()->currentCollisions.push_back(enemy->GetRigidBody());
						enemy->GetRigidBody()->currentCollisions.push_back(projectile->GetRigidBody());
					}
					else
					{
						//move this somewhere else
						projectile->GetRigidBody()->currentCollisions.erase(std::remove(projectile->GetRigidBody()->currentCollisions.begin(), projectile->GetRigidBody()->currentCollisions.end(), enemy->GetRigidBody()),
							projectile->GetRigidBody()->currentCollisions.end());
						enemy->GetRigidBody()->currentCollisions.erase(std::remove(enemy->GetRigidBody()->currentCollisions.begin(), enemy->GetRigidBody()->currentCollisions.end(), projectile->GetRigidBody()),
							enemy->GetRigidBody()->currentCollisions.end());
						if (projectile->GetRigidBody()->currentCollisions.empty())
						{
							projectile->GetRigidBody()->isColliding = false;
						}
						if (enemy->GetRigidBody()->currentCollisions.empty())
						{
							enemy->GetRigidBody()->isColliding = false;
						}
					}
				}
			}
		}

	}
	for (auto obstacle : m_pObstaclePool->GetPool())
	{
		//std::cout << m_pPlayer->GetTransform()->position.x << " , " << m_pPlayer->GetTransform()->position.y <<  std::endl;
		//std::cout << obstacle->GetTransform()->position.x<<" , " <<  obstacle->GetTransform()->position.y <<  std::endl;
		//std::cout << m_pShark->GetTransform()->position.x << " , " << m_pShark->GetTransform()->position.y << std::endl;

		// Hard-coded for now, can be moved into a function for the game object in general later so collision between all obstacles is seamless.
		if (CollisionManager::AABBCheck(m_pPlayer, obstacle))
		{
			std::cout << "obstacle collision" << std::endl;
			CollisionManager::ResolveCollisions(m_pPlayer, obstacle);
		}
		for (auto proj : m_pTorpedoPool->GetPool())
		{
			if(CollisionManager::AABBCheck(proj, obstacle))
			{
				proj->GetRigidBody()->isColliding = true;
				proj->GetRigidBody()->currentCollisions.push_back(obstacle->GetRigidBody());
			}
			else
			{
				proj->GetRigidBody()->currentCollisions.erase(std::remove(proj->GetRigidBody()->currentCollisions.begin(), proj->GetRigidBody()->currentCollisions.end(), obstacle->GetRigidBody()),
							proj->GetRigidBody()->currentCollisions.end());
				if (proj->GetRigidBody()->currentCollisions.empty())
				{
					proj->GetRigidBody()->isColliding = false;
				}
				
			}
			
		}

	}

	//only needed in play state, not start or end or pause.
	//each game object type will probably want to use a different type of collision
	//dont want to do object->checkcollision with all objects because then each collision will be checked twice
	//want to use distance checker to be within a certain range before checking collision.
}

void PlayScene::InitPools()
{
	// Instantiating the torpedo pool.
	m_pTorpedoPool = new TorpedoPool();
	AddChild(m_pTorpedoPool, PROJECTILES);

	// Instantiating the enemy pool.
	m_pEnemyPool = new EnemyPool();
	AddChild(m_pEnemyPool, ENEMIES);

	// Instantiating the obstacle pool.
	m_pObstaclePool = new ObstaclePool();
	AddChild(m_pObstaclePool, OBSTACLE);

}

void PlayScene::InitFPSCounter()
{
	// FPS Counter Set-Up
	m_pFpsCounter = new Label;
	m_pFpsCounter->SetEnabled(true);
	m_pFpsCounter->SetHeight(50);
	m_pFpsCounter->SetWidth(50);
	m_pFpsCounter->SetText("0 fps");
	m_pFpsCounter->GetTransform()->position = { 90.0f,30.0f };
	m_pFpsCounter->SetSize(40);
	m_pFpsCounter->SetColour({ 255,255,0,255 });
	if (!Game::Instance().GetDebugMode())
	{
		m_pFpsCounter->SetVisible(false);
	}
	AddChild(m_pFpsCounter, UI);
}

std::string PlayScene::GetGuiTitle()
{
	return m_guiTitle;
}

Player* PlayScene::GetPlayer()
{
	return m_pPlayer;
}

Background* PlayScene::GetBackground()
{
	return m_pBackground;
}

ObstaclePool* PlayScene::GetObstaclePool()
{
	return m_pObstaclePool;
}

EnemyPool* PlayScene::GetEnemyPool()
{
	return m_pEnemyPool;
}

TorpedoPool* PlayScene::GetTorpedoPool()
{
	return m_pTorpedoPool;
}

bool PlayScene::GetPlayerFacingRight()
{
	return m_playerFacingRight;
}

Label* PlayScene::GetFPSCounter()
{
	return m_pFpsCounter;
}

float PlayScene::GetTimer()
{
	return timer;
}

std::map<std::string, Obstacle*> PlayScene::GetTotalObstacles()
{
	return m_pTotalObstacles;
}

bool PlayScene::GetIsLevelEditing()
{
	return isLevelEditing;
}

bool PlayScene::GetIsObstacleDeleting()
{
	return isObstacleDeleting;
}

bool PlayScene::GetIsMouseHeld()
{
	return m_isMouseHeld;
}

bool PlayScene::GetIsObstacleBeingPlaced()
{
	return m_isObstacleBeingPlaced;
}

bool PlayScene::GetCurrentInputType()
{
	return m_pCurrentInputType;
}

void PlayScene::SetGuiTitle(std::string title)
{
	m_guiTitle = title;
}

void PlayScene::SetPlayer(Player* player)
{
	m_pPlayer = player;
}

void PlayScene::SetBackground(Background* background)
{
	m_pBackground = background;
}

void PlayScene::SetObstaclePool(ObstaclePool* pool)
{
	m_pObstaclePool = pool;
}

void PlayScene::SetEnemyPool(EnemyPool* pool)
{
	m_pEnemyPool = pool;
}

void PlayScene::SetTorpedoPool(TorpedoPool* pool)
{
	m_pTorpedoPool = pool;
}

void PlayScene::SetPlayerFacingRight(bool facing)
{
	m_playerFacingRight = facing;
}

void PlayScene::SetFPSCounter(Label* counter)
{
	m_pFpsCounter = counter;
}

void PlayScene::SetTimer(float time)
{
	timer = time;
}

void PlayScene::SetTotalObstacles(std::map<std::string, Obstacle*> totalObstacles)
{
	m_pTotalObstacles = totalObstacles;
}

void PlayScene::SetIsLevelEditing(bool editing)
{
	isLevelEditing = editing;
}

void PlayScene::SetIsObstacleDeleting(bool deleting)
{
	isObstacleDeleting = deleting;
}

void PlayScene::SetIsMouseHeld(bool held)
{
	m_isMouseHeld = held;
}

void PlayScene::SetIsObstacleBeingPlaced(bool placed)
{
	m_isObstacleBeingPlaced = placed;
}

void PlayScene::SetCurrentInputType(bool type)
{
	m_pCurrentInputType = type;
}


void PlayScene::GUI_Function() 
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Level Editor", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	ImGui::Text("Player Input");
	ImGui::RadioButton("Keyboard / Mouse", &m_pCurrentInputType, static_cast<int>(InputType::KEYBOARD_MOUSE)); ImGui::SameLine();
	ImGui::RadioButton("Game Controller", &m_pCurrentInputType, static_cast<int>(InputType::GAME_CONTROLLER)); ImGui::SameLine();
	ImGui::RadioButton("Both", &m_pCurrentInputType, static_cast<int>(InputType::ALL));

	ImGui::Separator();

	if (ImGui::Checkbox("Enable Level Editing", &isLevelEditing)) {
		Game::Instance().SetLevelEditorMode(isLevelEditing);
	}

	ImGui::Separator();

	ImGui::TextColored(ImVec4(1, 0, 0, 1), "Obstacles To Place");
	ImGui::BeginChild("Scrolling");
		for (std::pair<std::string, Obstacle*> obstacle : m_pTotalObstacles)
		{
			if (ImGui::Button(obstacle.first.c_str()))
			{
				const auto temp = new Obstacle(obstacle.first.c_str(), obstacle.second->textureName.c_str());

				temp->m_isPlacing = true;

				m_pObstaclePool->Spawn(temp);
				std::cout << obstacle.first;
			}

		}
	ImGui::EndChild();


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
