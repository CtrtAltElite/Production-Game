#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Background.h"
#include "Scene.h"
#include "Player.h"
#include "Button.h"
#include "Camera.h"
#include "Label.h"
#include "Obstacle.h"
#include "Torpedo.h"
#include "Enemy.h"
#include "LandFish.h"
#include "Pufferfish.h"
#include "SeaUrchin.h"
#include "Shark.h"
#include <string>
#include <fstream>
#include <map>

constexpr int NEXT_ENEMY_SPAWN = 50;
constexpr char* OBSTACLE_FILE_NAME = "../Assets/sprites/obstacles/obstacleList.txt";

class PlayScene : public Scene
{
public:
	PlayScene();
	virtual ~PlayScene() = default;

	// Inherited via Scene
	void Draw() override;
	void Update() override;
	void Clean() override;
	void HandleEvents() override;
	void Start() override;
	

	// Specific functions dedicated to PlayScene
	virtual void Collision();
	virtual void InitPools();
	void InitFPSCounter();

	std::string GetGuiTitle();
	Player* GetPlayer();
	Background* GetBackground();
	ObstaclePool* GetObstaclePool();
	EnemyPool* GetEnemyPool();
	TorpedoPool* GetTorpedoPool();
	bool GetPlayerFacingRight();
	Label* GetFPSCounter();
	float GetTimer();
	std::map<std::string, Obstacle*> GetTotalObstacles();
	bool GetIsLevelEditing();
	bool GetIsObstacleDeleting();
	bool GetIsMouseHeld();
	bool GetIsObstacleBeingPlaced();
	bool GetCurrentInputType();
	std::string GetCurrentObstacleFile() const;

	void SetGuiTitle(std::string title);
	void SetPlayer(Player* player);
	void SetBackground(Background* background);
	void SetObstaclePool(ObstaclePool* pool);
	void SetEnemyPool(EnemyPool* pool);
	void SetTorpedoPool(TorpedoPool* pool);
	void SetPlayerFacingRight(bool facing);
	void SetFPSCounter(Label* counter);
	void SetTimer(float time);
	void SetTotalObstacles(std::map<std::string, Obstacle*> totalObstacles);
	void SetIsLevelEditing(bool editing);
	void SetIsObstacleDeleting(bool deleting);
	void SetIsMouseHeld(bool held);
	void SetIsObstacleBeingPlaced(bool placed);
	void SetCurrentInputType(bool type);
	void SetCurrentObstacleFile(std::string current);

	Obstacle* CheckWhatObstacleToSpawn(std::string name);

	void AddToTotalObstacle(std::string name, Obstacle* obstacle);
	void GetPlayerInput();
	void SaveObstaclesToFile();
	void LoadObstaclesFromFile();
	void GUI_Function();

private:
	// IMGUI Function
	
	std::string m_guiTitle;
	Player* m_pPlayer{};

	// Objects for the PlayScene
	Background* m_pBackground{};
	ObstaclePool* m_pObstaclePool{};
	EnemyPool* m_pEnemyPool{};
	TorpedoPool* m_pTorpedoPool{};
	bool m_playerFacingRight{};
	Label* m_pFpsCounter{};
	float timer;

	// Variables for grabbing total obstacles and storing them
	std::map<std::string, Obstacle*> m_pTotalObstacles;


	// Level Editor variables
	bool isLevelEditing;
	bool isObstacleDeleting;
	bool m_isMouseHeld;
	bool m_isObstacleBeingPlaced;
	std::string currentLevelObstacleFile;
	

	// Input Control
	int m_pCurrentInputType{};
};

#endif /* defined (__PLAY_SCENE__) */