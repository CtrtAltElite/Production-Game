#pragma once
#ifndef __WHAT_SCENE__
#define __WHAT_SCENE__

#include "Scene.h"
#include "Label.h"
#include "Ship.h"
#include "Button.h"

class WHAT final : public Scene
{
public:
	WHAT();
	~WHAT() override;

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

#endif /* defined (__WHAT_SCENE__) */