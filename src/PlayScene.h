#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Player.h"
#include "Background.h"
#include "Projectile.h"
#include "box2d.h"
#include "Shark.h"


class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene() override;

	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;
	virtual void HandleEvents() override;
	virtual void Start() override;
	virtual void InitRigidBody() override;
	b2Body* GetRigidBody() override;
private:
	void GUI_Function() const;
	std::string m_guiTitle;
	int m_ScreenHeight; //probably already global constants
	int m_ScreenWidth;
	Player* m_pPlayer;
	Shark* m_pShark;
	Projectile* m_pProjectile;
	std::vector<Projectile*> m_pProjVec;
	Background* m_pBackground;
	b2Body* m_rigidBody;

};

#endif /* defined (__PLAY_SCENE__) */