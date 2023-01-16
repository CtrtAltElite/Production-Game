#pragma once
#ifndef __PROJECTILE__
#define __PROJECTILE__

#include "Player.h"
#include "Sprite.h"

class Projectile : public Sprite
{
public:
	Projectile(Player* player, SDL_Point mousePosition);
	// Life Cycle Methods
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;
private:
	float m_angle;
	float m_speed;
	float m_maxvelo;
};
#endif /* defined (__PROJECTILE__)*/