#pragma once
#ifndef __LEVEL_SELECTOR_H__
#define __LEVEL_SELECTOR_H__

#include <array>
#include "Scene.h"
#include "SceneState.h"


// All the level selection screens!
#include "StartScene.h"
#include "SelectScene.h"
#include "PrologueScene.h"

#include "LevelOneScene.h"
#include "LevelTwoScene.h"
#include "LevelThreeScene.h"
#include "BossScene.h"
#include "PlayScene.h"
#include "EndScene.h"



class LevelManager final 
{
public:
	// Constructor
	LevelManager();
	// Destructor
	virtual ~LevelManager();

	// Lifecycle variables
	static void Init();
	static void ChangeLevelSelection(SceneState state_to_change);
	static void UpdateLevel();
	static void RenderLevel();
	static void Clean();


private:

	static void InitLevelSelectionScreens();
	static std::array<Scene*, static_cast<int>(SceneState::NUM_OF_SCENES)> m_levelScreens;
	static Scene* m_pCurrentLevel;
};

#endif //!__LEVEL_SELECTOR_H__