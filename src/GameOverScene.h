#pragma once
#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "Scene.h"
#include "Label.h"
#include "Ship.h"
#include "Button.h"


class GameOverScene : public Scene
{
public:
	GameOverScene();
	~GameOverScene() override;

	// Inherited via Scene
	void Draw() override;
	void Update() override;
	void Clean() override;
	void HandleEvents() override;
	void Start() override;

private:
	Label* m_pStartLabel{};
	Label* m_pInstructionsLabel{};


	Button* m_pStartButton{};
};

#endif //!__GAME_OVER_SCREEN_H__