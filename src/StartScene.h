#pragma once
#ifndef __START_SCENE__
#define __START_SCENE__

#include "Scene.h"
#include "Label.h"
#include "Ship.h"
#include "Button.h"

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
	
private:
	Label* m_pStartLabel{};
	Label* m_pInstructionsLabel{};
	

	Button* m_pStartButton{};
};

#endif /* defined (__START_SCENE__) */