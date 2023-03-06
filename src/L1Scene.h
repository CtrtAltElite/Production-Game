#pragma once
#ifndef __L1_SCENE__
#define __L1_SCENE__

#include "Scene.h"
#include "Label.h"
#include "Ship.h"
#include "Button.h"

class L1S final : public Scene
{
public:
	L1S();
	~L1S() override;

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

#endif /* defined (__L1_SCENE__) */