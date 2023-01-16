#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Player.h"
#include "Background.h"
#include "Projectile.h"


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
	
	SDL_Point m_mousePosition;
	int m_ScreenHeight;
	int m_ScreenWidth;
	Player* m_pPlayer;
	Projectile* m_pProjectile;
	std::vector<Projectile*> m_pProjVec;
	bool m_playerFacingRight;
	Background* m_pBackground;

	// UI Items
};

#endif /* defined (__PLAY_SCENE__) */