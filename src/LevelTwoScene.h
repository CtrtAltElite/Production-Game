#pragma once
#ifndef __LEVEL_TWO_SCENE_H__
#define __LEVEL_TWO_SCENE_H__

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
#include "Pufferfish.h"
#include <string>
#include <fstream>
#include <map>

#include "PlayScene.h"

class LevelTwoScene final : public PlayScene
{
public:
	LevelTwoScene();
	~LevelTwoScene() override;

	// Inherited via Scene
	void Draw() override;
	void Update() override;
	void Clean() override;
	void HandleEvents() override;
	void Start() override;
	

	// Specific functions dedicated to PlayScene
	void Collision() override;
	void InitPools() override;
	void SaveObstaclesToFile();
	void LoadObstaclesToFile();

	

private:
};

#endif /* defined (__LEVEL_TWO_SCENE_H__) */