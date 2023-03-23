#pragma once
#ifndef __BOSS_SCENE_H__
#define __BOSS_SCENE_H__

#include "Scene.h"
#include "Label.h"
#include "Ship.h"
#include "Button.h"

class BossScene final : public Scene
{
public:
	BossScene();
	~BossScene() override;

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
	Button* m_pNextButton{};
	Button* m_pPrevButton{};
};

#endif /* defined (__BOSS_SCENE_H__) */