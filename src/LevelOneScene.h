#pragma once
#ifndef __LEVEL_ONE_SCENE_H__
#define __LEVEL_ONE_SCENE_H__

#include "Background.h"
#include "Scene.h"
#include "Player.h"
#include "Button.h"
#include "Camera.h"
#include "Label.h"
#include "Obstacle.h"
#include "Torpedo.h"
#include "Enemy.h"
#include "Shark.h"
#include <string>
#include <fstream>
#include <map>


class LevelOneScene final : public Scene
{
public:
	LevelOneScene();
	~LevelOneScene() override;

	// Inherited via Scene
	void Draw() override;
	void Update() override;
	void Clean() override;
	void HandleEvents() override;
	void Start() override;
	

	// Specific functions dedicated to PlayScene
	void Collision();
	void InitPools();
	void InitFPSCounter();
	void SaveObstaclesToFile();
	void LoadObstaclesToFile();

private:
	// IMGUI Function
	void GUI_Function();
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

	Obstacle* CheckWhatObstacleToSpawn(std::string name);

	// Input Control
	int m_pCurrentInputType{};
	void GetPlayerInput();
};

#endif /* defined (__LEVEL_ONE_SCENE_H__) */