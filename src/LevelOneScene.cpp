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
	if (m_pObstaclePool != nullptr) {
		m_pObstaclePool->Update();
	}
	

	if (m_isMouseHeld) // If we are currently in level editor mode and are holding the mouse.
	{
		// If an object is not being placed
		if (!m_isObstacleBeingPlaced) {
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
			for (auto obstacle : m_pObstaclePool->GetPool()) {
				if (obstacle->m_isPlacing == false) {
					++counter;
				}
				if (counter == m_pObstaclePool->GetPool().size() - 1) {
					m_isObstacleBeingPlaced = false;
				}
			}
		}	
		
	}

	if (m_pPlayer != nullptr && !m_pPlayer->GetIsDead()) { // As long as the player is not dead.
		if (!LevelManager::IsLevelPaused() && !Game::Instance().GetLevelEditorMode()) { // If we currently are not paused and level editor mode is not enabled.
		//Game::Instance().SetDebugMode(false);
			Collision();
			UpdateDisplayList();
			Game::Instance().SetLevelBoundaries({ Game::Instance().GetLevelBoundaries().x,Game::Instance().GetLevelBoundaries().y,(Game::Instance().GetLevelBoundaries().z - Game::Instance().GetLevelBoundaries().w) < 0 ? Game::Instance().GetLevelBoundaries().z + 0.2f : Game::Instance().GetLevelBoundaries().z ,Game::Instance().GetLevelBoundaries().w });
			Camera::Instance().GetTransform()->position.x = Util::Clamp(Camera::Instance().GetTransform()->position.x, Game::Instance().GetLevelBoundaries().x, Game::Instance().GetLevelBoundaries().y);
			Camera::Instance().GetTransform()->position.y = Util::Clamp(Camera::Instance().GetTransform()->position.y, Game::Instance().GetLevelBoundaries().z, Game::Instance().GetLevelBoundaries().w);

			if (m_pEnemyPool != nullptr)
			{
				m_pEnemyPool->Update();
				m_pEnemyPool->UpdateTargetPlayer(m_pPlayer);
			}


			if (timer <= 0)
			{
				timer = NEXT_ENEMY_SPAWN;
				auto shark = new Shark;
				shark->SetTargetPlayer(m_pPlayer);
				m_pEnemyPool->Spawn(shark);
				
				shark = new Shark;
				shark->SetTargetPlayer(m_pPlayer);
				m_pEnemyPool->Spawn(shark);

				//auto stingray = new Stingray;
				//stingray->GetTransform()->position = glm::vec2(Camera::Instance().GetTransform()->position.x, rand() % 5 + m_pPlayer->GetTransform()->position.y);
				//m_pObstaclePool->Spawn(stingray);

				//auto jellyfish = new Jellyfish;
				//jellyfish->GetTransform()->position = glm::vec2(m_pPlayer->GetTransform()->position.x, m_pPlayer->GetTransform()->position.y - 800.0f);
				//m_pObstaclePool->Spawn(jellyfish);
				//m_pEnemyPool->UpdateTargetPlayer(m_pPlayer);
			}
			timer -= 0.1f;
		}
	}

	if (m_pPlayer != nullptr && m_pPlayer->GetIsDead() && !LevelManager::IsGameOver())
	{
		LevelManager::SetGameOver(true);
	}
	
	
	// Set FPS display on screen.
	if ((SDL_GetTicks64() / 1000) > 0)
	{
		const Uint64 fps = Game::Instance().GetFrames() / (SDL_GetTicks64() / 1000);
		const std::string fpsText = "FPS: " + std::to_string(fps);
		m_pFpsCounter->SetText(fpsText);
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
			m_isMouseHeld = true;
			// Check for obstacle collision, if so then delete said obstacle
			for (auto obstacle : m_pObstaclePool->GetPool()) {
				if (!m_isObstacleBeingPlaced && isObstacleDeleting) { // Well, we cannot delete something if an obstacle is being placed!
					if (CollisionManager::PointRectCheck(EventManager::Instance().GetMousePosition() + Camera::Instance().GetTransform()->position, obstacle->GetTransform()->position, obstacle->GetWidth(), obstacle->GetHeight())) {
						obstacle->SetDeleteMe(true);
					}
				}
				else { // Set obstacle deletion to 0 since we are not placing an obstacle
					isObstacleDeleting = false;
				}

			}
		}
		else if (EventManager::Instance().MouseReleased(1)) {
			m_isMouseHeld = false;
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
Obstacle* LevelOneScene::CheckWhatObstacleToSpawn(std::string name)
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
	return nullptr;
}

void LevelOneScene::GetPlayerInput()
{
	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_SPACE))
	{
		m_pPlayer->MoveAtMouse();
	}
	if (EventManager::Instance().MousePressed(1)) //left mouse button
	{
		m_pTorpedoPool->Fire();
		//SoundManager::Instance().PlaySound("playerShoot"); //ITS SO LOUD LOL
	}
}

void LevelOneScene::Start()
{
	m_guiTitle = "Level 1";

	SoundManager::Instance().SetMusicVolume(25);
	SoundManager::Instance().Load("../Assets/audio/LevelMusic/LevelOne/Dancing_with_Dolphins.mp3", "levelOneMusic", SoundType::SOUND_MUSIC);
	SoundManager::Instance().PlayMusic("levelOneMusic", -1, 1);

	Camera::Instance().SetEnabled(true);
	Game::Instance().SetDebugMode(false);

	// Player Sprite
	m_pPlayer = new Player;
	Game::Instance().SetPlayer(m_pPlayer);
	m_pPlayer->SetIsCentered(true);
	m_pPlayer->GetTransform()->position={Config::SCREEN_WIDTH/2,Config::SCREEN_HEIGHT/2};
	AddChild(m_pPlayer, PLAYERS);
	m_playerFacingRight = true;


	m_pBackground = new Background("../Assets/textures/Levels/1st_level.png", "firstLevel");
	m_pBackground->GetTransform()->position = glm::vec2(-Config::SCREEN_WIDTH/2-160, 0);
	m_pBackground->SetScale(2.5f);
	AddChild(m_pBackground, BACKGROUND);

	Game::Instance().SetLevelBoundaries({ 0- m_pBackground->GetWidth()*m_pBackground->GetScale() / 2, m_pBackground->GetWidth()*m_pBackground->GetScale()/2-Config::SCREEN_WIDTH,0, m_pBackground->GetHeight()*m_pBackground->GetScale()-Config::SCREEN_HEIGHT});

	InitPools();
	
	Game::Instance().SetPlayer(m_pPlayer);
	m_pEnemyPool->Spawn(new Shark);

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
				m_pTotalObstacles.emplace(std::pair<std::string, Obstacle*>(textureName, temp));
				std::cout << imageType << std::endl << fileName << std::endl << textureName << std::endl;
			}
			else if (imageType == "spritesheet") { // it is a spritesheet
				// TODO: make a switch case for each obstacle
				obstacleFile >> textureName >> fileName >> textFile;
				auto temp = new Obstacle(textureName.c_str(), fileName.c_str(), textFile.c_str());
				m_pTotalObstacles.emplace(std::pair<std::string, Obstacle*>(textureName, temp));
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
	

	bgObj->GetTransform()->position = m_pBackground->GetTransform()->position;


	m_pObstaclePool->Spawn(bgObj);

	m_pPlayer->GetTransform()->position = m_pBackground->GetTransform()->position;

	LoadObstaclesToFile();
	ImGuiWindowFrame::Instance().SetGuiFunction([this] { GUI_Function(); });
}

void LevelOneScene::Collision()
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

void LevelOneScene::InitPools()
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

void LevelOneScene::InitFPSCounter()
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

void LevelOneScene::SaveObstaclesToFile()
{
	std::fstream file("../Assets/data/Levels/Level1Obstacles.txt");
	if (file.is_open())
	{
		file.clear();

		for (auto obstacle : m_pObstaclePool->GetPool())
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
			m_pObstaclePool->Spawn(temp);

			temp->GetTransform()->position = { x, y };
		}
		file.close();
	}
}

void LevelOneScene::GUI_Function()
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
		isObstacleDeleting = false;
	}

	ImGui::Separator();

	if (Game::Instance().GetLevelEditorMode()) {
		if (ImGui::Checkbox("Enable Obstacle Deletion Mode", &isObstacleDeleting)) {

		}
		if (ImGui::Button("Save Obstacles"))
		{
			SaveObstaclesToFile();
		}
	}

	ImGui::Separator();

	ImGui::TextColored(ImVec4(1, 0, 0, 1), "Obstacles To Place");
	ImGui::BeginChild("Scrolling");
	for (std::pair<std::string, Obstacle*> obstacle : m_pTotalObstacles)
	{
		if (ImGui::Button(obstacle.first.c_str()))
		{
			if (Game::Instance().GetLevelEditorMode()) {
				
				Obstacle* temp = CheckWhatObstacleToSpawn(obstacle.first);
				
				if (temp != nullptr)
				{
					m_isObstacleBeingPlaced = true;
					temp->m_isPlacing = true;

					m_pObstaclePool->Spawn(temp);
					std::cout << obstacle.first;
				}
			}
			else {
				ImGui::SameLine();
				ImGui::Text("Please Enable Level Editing First.");
			}
		}

	}
	ImGui::EndChild();


	ImGui::Separator();






	ImGui::End();
}