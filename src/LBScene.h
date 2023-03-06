#pragma once
#ifndef __LB_SCENE__
#define __LB_SCENE__

#include "Scene.h"
#include "Label.h"
#include "Ship.h"
#include "Button.h"

class LBS final : public Scene
{
public:
	LBS();
	~LBS() override;

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

#endif /* defined (__LB_SCENE__) */