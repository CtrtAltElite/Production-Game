#pragma once
#ifndef __PROJECTILE__
#define __PROJECTILE__

#include "Player.h"
#include "Sprite.h"

class Projectile : public Sprite
{
public:
	Projectile(Player* player);
	// Life Cycle Methods
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;
	void InitRigidBody() override;
	b2Body* GetRigidBody() override;
private:
	int mouseX;
	int mouseY;
	float m_angle;
	float m_maxvelo;
	b2Body* m_rigidBody;
};
#endif /* defined (__PROJECTILE__)*/