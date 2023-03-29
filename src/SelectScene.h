#pragma once
#ifndef __SELECT_SCENE_H__
#define __SELECT_SCENE_H__

#include "Scene.h"
#include "Label.h"
#include "Ship.h"
#include "Button.h"
#include "MenuPlayer.h"
#include "Background.h"
#include "Obstacle.h"

const int SELECT_SCREEN_WIDTH = 1024;
const int SELECT_SCREEN_HEIGHT = 768;

const int LEVELS = 3;

class SelectScene : public Scene {
public:
	SelectScene();
	~SelectScene() override;

	// Inherited via Scene
	void Draw() override;
	void Update() override;
	void Clean() override;
	void HandleEvents() override;
	void Start() override;

private:
	ObstaclePool* m_pObstaclePool;

	MenuPlayer* m_player{};
	Background* m_pBackground{};
	Background* m_pFloorBackground{};
	Button* m_pStartButton{};

	void InitLevelSelectionObstacles();

};

#endif //!__SELECT_SCENE_H__