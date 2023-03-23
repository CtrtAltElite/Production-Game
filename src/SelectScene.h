#pragma once
#ifndef __SELECT_SCENE_H__
#define __SELECT_SCENE_H__

#include "Scene.h"
#include "Label.h"
#include "Ship.h"
#include "Button.h"

class SelectScene : public Scene {
public:
	SelectScene();
	~SelectScene() override;

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

#endif //!__SELECT_SCENE_H__