#pragma once
#ifndef __L2_SCENE__
#define __L2_SCENE__

#include "Scene.h"
#include "Label.h"
#include "Ship.h"
#include "Button.h"

class L2S final : public Scene
{
public:
	L2S();
	~L2S() override;

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

#endif /* defined (__L2_SCENE__) */