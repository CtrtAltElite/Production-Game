#pragma once
#ifndef __TUTORIAL_SCENE_H__
#define __TUTORIAL_SCENE_H__

#include "Scene.h"
#include "Label.h"
#include "Ship.h"
#include "Button.h"
#include "MenuPlayer.h"
#include "Background.h"
#include "Obstacle.h"
#include "Torpedo.h"

class TutorialScene : public Scene {
public:
	TutorialScene();
	~TutorialScene() override;

	// Inherited via Scene
	void Draw() override;
	void Update() override;
	void Clean() override;
	void HandleEvents() override;
	void Start() override;

	void SayText(const std::string& textToSay);

private:
	ObstaclePool* m_pObstaclePool;

	bool m_isInCutscene = false;
	bool m_isTyping = false;	
	float timerUntilNextType = 0;
	float maxTimer = 0.1f;
	int stringIterator = 0;
	std::string current_text;

	bool m_textDisplayed = false;
	bool m_playerFacingRight{};

	TorpedoPool* m_pTorpedoPool{};
	Player* m_pPlayer{};
	Background* textBar{};
	Background* m_pBackground{};
	Label* m_pText;
	Background* m_pFloorBackground{};
};

#endif //!__TUTORIAL_SCENE_H__