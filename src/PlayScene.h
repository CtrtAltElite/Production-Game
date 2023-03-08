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
#include "Shark.h"

constexpr int NEXT_ENEMY_SPAWN = 50;

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene() override;

	// Scene LifeCycle Functions
	void Draw() override;
	void Update() override;
	void Clean() override;
	void HandleEvents() override;
	void Start() override;

	// Specific functions dedicated to PlayScene
	void Collision();
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
	std::vector<Obstacle*>m_pObstacles;
	bool m_playerFacingRight{};
	Label* m_pFpsCounter{};
	float timer;
	

	
	// Input Control
	int m_pCurrentInputType{};
	void GetPlayerInput();
};

#endif /* defined (__PLAY_SCENE__) */