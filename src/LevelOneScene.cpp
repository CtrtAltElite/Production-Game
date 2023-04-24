#include "LevelOneScene.h"
#include "Game.h"
#include "EventManager.h"
// required for IMGUI
#include "InputType.h"

#include <typeinfo>

#include "Camera.h"
#include "imgui.h"
#include "imgui_sdl.h"
#include "Jellyfish.h"
#include "Renderer.h"
#include "Torpedo.h"
#include "Util.h"
#include "Layers.h"
#include "Stingray.h"
#include "SeaUrchin.h"
#include "LandFish.h"
#include "LevelManager.h"

LevelOneScene::LevelOneScene()
{
}

LevelOneScene::~LevelOneScene()
= default;

void LevelOneScene::Draw()
{
	DrawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance().GetRenderer(), 255, 255, 255, 255);
}

void LevelOneScene::Update()
{
	// Update the obstacle pool!
	if (GetObstaclePool() != nullptr) {
		GetObstaclePool()->Update();
	}
	

	if (GetIsMouseHeld()) // If we are currently in level editor mode and are holding the mouse.
	{
		// If an object is not being placed
		if (!GetIsObstacleBeingPlaced()) {
			// Moves camera based on mouse position
			if (EventManager::Instance().GetMousePosition().x >= 400) {
				Camera::Instance().GetTransform()->position.x += 10.0f;
			}
			else {
				Camera::Instance().GetTransform()->position.x -= 10.0f;
			}
			if (EventManager::Instance().GetMousePosition().y >= 400) {
				Camera::Instance().GetTransform()->position.y += 10.0f;
			}
			else {
				Camera::Instance().GetTransform()->position.y -= 10.0f;
			}
			
			Camera::Instance().GetTransform()->position.x = Util::Clamp(Camera::Instance().GetTransform()->position.x, Game::Instance().GetLevelBoundaries().x - 250, Game::Instance().GetLevelBoundaries().y + 250);
			Camera::Instance().GetTransform()->position.y = Util::Clamp(Camera::Instance().GetTransform()->position.y, Game::Instance().GetLevelBoundaries().z - 250, Game::Instance().GetLevelBoundaries().w + 250);

		}
		else {
			int counter = 0;
			for (auto obstacle : GetObstaclePool()->GetPool()) {
				if (obstacle->m_isPlacing == false) {
					++counter;
				}
				if (counter == GetObstaclePool()->GetPool().size() - 1) {
					SetIsObstacleBeingPlaced(false);
				}
			}
		}	
		
	}

	if (GetPlayer() != nullptr && !GetPlayer()->GetIsDead()) { // As long as the player is not dead.
		if (!LevelManager::IsLevelPaused() && !Game::Instance().GetLevelEditorMode()) { // If we currently are not paused and level editor mode is not enabled.
		//Game::Instance().SetDebugMode(false);
			Collision();
			UpdateDisplayList();
			Game::Instance().SetLevelBoundaries({ Game::Instance().GetLevelBoundaries().x,Game::Instance().GetLevelBoundaries().y,(Game::Instance().GetLevelBoundaries().z - Game::Instance().GetLevelBoundaries().w) < 0 ? Game::Instance().GetLevelBoundaries().z + 0.2f : Game::Instance().GetLevelBoundaries().z ,Game::Instance().GetLevelBoundaries().w });
			Camera::Instance().GetTransform()->position.x = Util::Clamp(Camera::Instance().GetTransform()->position.x, Game::Instance().GetLevelBoundaries().x, Game::Instance().GetLevelBoundaries().y);
			Camera::Instance().GetTransform()->position.y = Util::Clamp(Camera::Instance().GetTransform()->position.y, Game::Instance().GetLevelBoundaries().z, Game::Instance().GetLevelBoundaries().w);

			if (GetEnemyPool() != nullptr)
			{
				GetEnemyPool()->Update();
				GetEnemyPool()->UpdateTargetPlayer(GetPlayer());
			}


			if (GetTimer() <= 0)
			{
				SetTimer(NEXT_ENEMY_SPAWN);
				auto shark = new Shark;
				shark->SetTargetPlayer(GetPlayer());
				GetEnemyPool()->Spawn(shark);
				
				shark = new Shark;
				shark->SetTargetPlayer(GetPlayer());
				GetEnemyPool()->Spawn(shark);

				//auto stingray = new Stingray;
				//stingray->GetTransform()->position = glm::vec2(Camera::Instance().GetTransform()->position.x, rand() % 5 + m_pPlayer->GetTransform()->position.y);
				//m_pObstaclePool->Spawn(stingray);

				//auto jellyfish = new Jellyfish;
				//jellyfish->GetTransform()->position = glm::vec2(m_pPlayer->GetTransform()->position.x, m_pPlayer->GetTransform()->position.y - 800.0f);
				//m_pObstaclePool->Spawn(jellyfish);
				//m_pEnemyPool->UpdateTargetPlayer(m_pPlayer);
			}
			SetTimer(GetTimer()-0.1f);
		}
	}

	if (GetPlayer() != nullptr && GetPlayer()->GetIsDead() && !LevelManager::IsGameOver())
	{
		LevelManager::SetGameOver(true);
	}
	
	
	// Set FPS display on screen.
	if ((SDL_GetTicks64() / 1000) > 0)
	{
		const Uint64 fps = Game::Instance().GetFrames() / (SDL_GetTicks64() / 1000);
		const std::string fpsText = "FPS: " + std::to_string(fps);
		GetFPSCounter()->SetText(fpsText);
	}
}

void LevelOneScene::Clean()
{
	SaveObstaclesToFile();
	RemoveAllChildren();
}

void LevelOneScene::HandleEvents()
{
	EventManager::Instance().Update();

	// Are we in level editor mode AND this window is the main focus.
	if (Game::Instance().GetLevelEditorMode() && EventManager::Instance().IsMainWindowInFocus()) {
		if (EventManager::Instance().MousePressed(1)) { // If left click is pressed
			SetIsMouseHeld(true);
			// Check for obstacle collision, if so then delete said obstacle
			for (auto obstacle : GetObstaclePool()->GetPool()) {
				if (!GetIsObstacleBeingPlaced() && GetIsObstacleDeleting()) { // Well, we cannot delete something if an obstacle is being placed!
					if (CollisionManager::PointRectCheck(EventManager::Instance().GetMousePosition() + Camera::Instance().GetTransform()->position, obstacle->GetTransform()->position, obstacle->GetWidth(), obstacle->GetHeight())) {
						obstacle->SetDeleteMe(true);
					}
				}
				else { // Set obstacle deletion to 0 since we are not placing an obstacle
					SetIsObstacleDeleting(false);
				}

			}
		}
		else if (EventManager::Instance().MouseReleased(1)) {
			SetIsMouseHeld(false);
		}
	}

	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_P)) {
		if (!LevelManager::IsLevelPaused()) {
			LevelManager::SetPause(true);
		}
	}

	if (!LevelManager::IsLevelPaused() && !LevelManager::IsGameOver() && !Game::Instance().GetLevelEditorMode()) {
		GetPlayerInput();
	}
}

// Helps to figure out which obstacle should be spawned in!


void LevelOneScene::Start()
{
	SetGuiTitle("Level 1");

	SoundManager::Instance().SetMusicVolume(25);
	SoundManager::Instance().Load("../Assets/audio/LevelMusic/LevelOne/Dancing_with_Dolphins.mp3", "levelOneMusic", SoundType::SOUND_MUSIC);
	SoundManager::Instance().PlayMusic("levelOneMusic", -1, 1);

	Camera::Instance().SetEnabled(true);
	Game::Instance().SetDebugMode(false);

	// Player Sprite
	SetPlayer(new Player);
	Game::Instance().SetPlayer(GetPlayer());
	GetPlayer()->SetIsCentered(true);
	GetPlayer()->GetTransform()->position={Config::SCREEN_WIDTH/2,Config::SCREEN_HEIGHT/2};
	AddChild(GetPlayer(), PLAYERS);
	SetPlayerFacingRight(true);


	SetBackground(new Background("../Assets/textures/Levels/1st_level.png", "firstLevel"));
	GetBackground()->GetTransform()->position = glm::vec2(-Config::SCREEN_WIDTH/2-160, 0);
	GetBackground()->SetScale(2.5f);
	AddChild(GetBackground(), BACKGROUND);

	Game::Instance().SetLevelBoundaries({ 0- GetBackground()->GetWidth()*GetBackground()->GetScale() / 2, GetBackground()->GetWidth()*GetBackground()->GetScale()/2-Config::SCREEN_WIDTH,0, GetBackground()->GetHeight()*GetBackground()->GetScale()-Config::SCREEN_HEIGHT});

	InitPools();
	
	Game::Instance().SetPlayer(GetPlayer());
	GetEnemyPool()->Spawn(new Shark);

	// Opening and initializing obstacle file!
	std::ifstream obstacleFile(OBSTACLE_FILE_NAME);

	// Writing obstacles to the map along with their name
	if (obstacleFile.is_open()) {
		std::string fileName;
		std::string textureName;
		std::string textFile;
		std::string imageType;
		while (!obstacleFile.eof()) {
			obstacleFile >> imageType;
			if (imageType == "image") // it is an image
			{
				obstacleFile >> textureName >> fileName;
				auto temp = new Obstacle(textureName.c_str(), fileName.c_str());
				GetTotalObstacles().emplace(std::pair<std::string, Obstacle*>(textureName, temp));
				std::cout << imageType << std::endl << fileName << std::endl << textureName << std::endl;
			}
			else if (imageType == "spritesheet") { // it is a spritesheet
				// TODO: make a switch case for each obstacle
				obstacleFile >> textureName >> fileName >> textFile;
				auto temp = new Obstacle(textureName.c_str(), fileName.c_str(), textFile.c_str());
				GetTotalObstacles().emplace(std::pair<std::string, Obstacle*>(textureName, temp));
				std::cout << imageType << std::endl << fileName << std::endl << textureName << std::endl;
			}
			else { // Oopsies an error ran.

			}

		}
		obstacleFile.close();
	}
	else {
		std::cout << "Could not open file!\n";
	}

	InitFPSCounter();

	Obstacle* bgObj = new Obstacle("firstLevelObstacles", "../Assets/sprites/obstacles/levelimages/firstLevelObstacles.png", 3);
	

	bgObj->GetTransform()->position = GetBackground()->GetTransform()->position;


	GetObstaclePool()->Spawn(bgObj);

	GetPlayer()->GetTransform()->position = GetBackground()->GetTransform()->position;

	LoadObstaclesToFile();
	ImGuiWindowFrame::Instance().SetGuiFunction([this] { GUI_Function(); });
}

void LevelOneScene::Collision()
{
	//there is a better way to do this
	//we need each rigid body to have a vector of collisions anyway to be able to collide with multiple objects (i think)
	//we could use something like this to build the vectors
	//then iterate, manage and do actions with the information fomr the vectors in the objects own updates

	for (auto enemy : GetEnemyPool()->GetPool())
	{
		if (Util::Distance(enemy->GetTransform()->position, GetPlayer()->GetTransform()->position) < 100.0f)
		{
			if (CollisionManager::AABBCheck(enemy, GetPlayer()))
			{
				std::cout << "Enemy player collision" << ::std::endl;
				enemy->GetRigidBody()->isColliding = true;
				enemy->GetRigidBody()->currentCollisions.push_back(GetPlayer()->GetRigidBody());
				GetPlayer()->GetRigidBody()->isColliding = true;
				GetPlayer()->GetRigidBody()->currentCollisions.push_back(enemy->GetRigidBody());
				GetPlayer()->TakeDamage(enemy->GetAttackDamage());
				//make vector of current collisions and pass enemy and m_pPlayer in. so we can have multiple collisions at the same time and access damage values
				//Game::Instance().ChangeSceneState(SceneState::END);
			}
			else
			{
				GetPlayer()->GetRigidBody()->currentCollisions.erase(std::remove(GetPlayer()->GetRigidBody()->currentCollisions.begin(), GetPlayer()->GetRigidBody()->currentCollisions.end(), GetPlayer()->GetRigidBody()),
					GetPlayer()->GetRigidBody()->currentCollisions.end());
				enemy->GetRigidBody()->currentCollisions.erase(std::remove(enemy->GetRigidBody()->currentCollisions.begin(), enemy->GetRigidBody()->currentCollisions.end(), enemy->GetRigidBody()),
					enemy->GetRigidBody()->currentCollisions.end());

				if (GetPlayer()->GetRigidBody()->currentCollisions.empty())
				{
					GetPlayer()->GetRigidBody()->isColliding = false;
				}
				if (enemy->GetRigidBody()->currentCollisions.empty())
				{
					enemy->GetRigidBody()->isColliding = false;
				}
			}
		}
		for (auto projectile : GetTorpedoPool()->GetPool())
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
	for (auto obstacle : GetObstaclePool()->GetPool())
	{
		//std::cout << m_pPlayer->GetTransform()->position.x << " , " << m_pPlayer->GetTransform()->position.y <<  std::endl;
		//std::cout << obstacle->GetTransform()->position.x<<" , " <<  obstacle->GetTransform()->position.y <<  std::endl;
		//std::cout << m_pShark->GetTransform()->position.x << " , " << m_pShark->GetTransform()->position.y << std::endl;

		// Hard-coded for now, can be moved into a function for the game object in general later so collision between all obstacles is seamless.
		if (CollisionManager::AABBCheck(GetPlayer(), obstacle))
		{
			std::cout << "obstacle collision" << std::endl;
			CollisionManager::ResolveCollisions(GetPlayer(), obstacle);
		}
		for (auto proj : GetTorpedoPool()->GetPool())
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

void LevelOneScene::InitPools()
{
	// Instantiating the torpedo pool.
	SetTorpedoPool(new TorpedoPool());
	AddChild(GetTorpedoPool(), PROJECTILES);

	// Instantiating the enemy pool.
	SetEnemyPool(new EnemyPool());
	AddChild(GetEnemyPool(), ENEMIES);

	// Instantiating the obstacle pool.
	SetObstaclePool(new ObstaclePool());
	AddChild(GetObstaclePool(), OBSTACLE);

}


void LevelOneScene::SaveObstaclesToFile()
{
	std::fstream file("../Assets/data/Levels/Level1Obstacles.txt");
	if (file.is_open())
	{
		file.clear();

		for (auto obstacle : GetObstaclePool()->GetPool())
		{
			if (!obstacle->textureName.empty())
			{
				file << obstacle->textureName << " " << obstacle->GetTransform()->position.x << " " << obstacle->GetTransform()->position.y;
				file << "\n";
			}
		}
		file.close();
		std::cout << "Obstacles Saved!\n";
	}
}

void LevelOneScene::LoadObstaclesToFile()
{
	std::fstream file("../Assets/data/Levels/Level1Obstacles.txt");
	if (file.is_open())
	{
		std::string name;
		float x, y;

		while (!file.eof())
		{
			file >> name >> x >> y;
			std::cout << name << std::endl;
			Obstacle* temp = CheckWhatObstacleToSpawn(name);
			if (temp != nullptr)
			{
				GetObstaclePool()->Spawn(temp);

				temp->GetTransform()->position = { x, y };
			}
			else {
				std::cout << "Error loading obstacle from file to game!\n";
			}
			
		}
		file.close();
	}
}



