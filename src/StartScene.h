#pragma once
#ifndef __START_SCENE__
#define __START_SCENE__

#include "Scene.h"
#include "Label.h"
#include "Ship.h"
#include "Button.h"

// Enum for the states of the start scene, so going through states in scene is easier!
enum START_SCENE_STATE {
	MENU,
	ASK_TUTORIAL,
	LOADING
};

class StartScene final : public Scene
{
public:
	StartScene();
	~StartScene() override;

	// Inherited via Scene
	void Draw() override;
	void Update() override;
	void Clean() override;
	void HandleEvents() override;
	void Start() override;

	void ChangeCurrentState(START_SCENE_STATE curState);
	
private:
	Label* m_pStartLabel{}; // MENU
	Label* m_pExitLabel{}; // MENU
	Label* m_pTutorialLabel{}; // ASK_TUTORIAL
	Label* m_pNoTutorialLabel{}; // ASK_TUTORIAL
	Label* m_pBackLabel{}; // ASK_TUTORIAL
	Label* m_pInstructionsLabel{}; // MENU
	
	bool mouseAlreadyPressed = false;

	Button* m_pStartButton{}; // MENU
	Button* m_pExitButton{}; // MENU
	Button* m_pTutorialButton{}; //ASK_TUTORIAL
	Button* m_pNoTutorialButton{}; // ASK_TUTORIAL
	Button* m_pBackButton{}; // ASK_TUTORIAL
};

#endif /* defined (__START_SCENE__) */