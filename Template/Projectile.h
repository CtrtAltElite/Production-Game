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
private:

};
#endif /* defined (__PROJECTILE__)*/