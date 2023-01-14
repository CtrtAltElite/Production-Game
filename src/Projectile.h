#pragma once
#ifndef __PROJECTILE__
#define __PROJECTILE__

#include "Sprite.h"

class Projectile: public Sprite
{
public:
	Projectile();
	~Projectile() override;
	// Life Cycle Methods
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;
private:
};
#endif /* defined (__PROJECTILE__)*/