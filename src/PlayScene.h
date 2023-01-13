#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Player.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene() override;

	// Scene LifeCycle Functions
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;
	virtual void HandleEvents() override;
	virtual void Start() override;
private:
	// IMGUI Function
	void GUI_Function() const;
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	Player* m_pPlayer;
	bool m_playerFacingRight;

	// UI Items
};

#endif /* defined (__PLAY_SCENE__) */