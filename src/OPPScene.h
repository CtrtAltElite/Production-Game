#pragma once
#ifndef __OPP_SCENE__
#define __OPP_SCENE__

#include "Scene.h"
#include "Label.h"
#include "Ship.h"
#include "Button.h"

class OPP final : public Scene
{
public:
	OPP();
	~OPP() override;

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

#endif /* defined (__START_SCENE__) */