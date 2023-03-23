#pragma once
#ifndef __LEVEL_ONE_SCENE_H__
#define __LEVEL_ONE_SCENE_H__

#include "Scene.h"
#include "Label.h"
#include "Ship.h"
#include "Button.h"

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
	
private:
	Label* m_pStartLabel{};
	Label* m_pInstructionsLabel{};
	

	Button* m_pStartButton{};
	Button* m_pNextButton{};
	Button* m_pPrevButton{};

};

#endif /* defined (__LEVEL_ONE_SCENE_H__) */