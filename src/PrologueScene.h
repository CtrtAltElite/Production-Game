#pragma once
#ifndef __PROGOLUE_SCENE_H__
#define __PROGOLUE_SCENE_H__

#include "Scene.h"
#include "Label.h"
#include "Ship.h"
#include "Button.h"

class PrologueScene final : public Scene
{
public:
	PrologueScene();
	~PrologueScene() override;

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

#endif /* defined (__PROGOLUE_SCENE_H__) */