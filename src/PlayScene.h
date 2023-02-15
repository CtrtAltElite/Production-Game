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
#include "Shark.h"

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
	void Collision();
	void DeleteFlagged();
private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;
	
	Player* m_pPlayer{};
	Background* m_pBackground{};
	Projectile* m_pProjectile{};
	Shark* m_pShark{};
	Obstacle* m_pObstacle{};
	std::vector<Enemy*>m_pEnemies{};
	TorpedoPool* m_torpedoPool;
	std::vector<Obstacle*>m_pObstacles;
	bool m_playerFacingRight{};
	Label* m_pFpsCounter{};

	

	
	// Input Control
	int m_pCurrentInputType{};
	void GetPlayerInput();
};

#endif /* defined (__PLAY_SCENE__) */