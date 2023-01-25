#pragma once
#ifndef __ENEMY__
#define __ENEMY
#include "Sprite.h"
class Enemy : public DisplayObject
{
public:
	Enemy();
	virtual ~Enemy();

	// Life Cycle Methods
	virtual void Draw() override=0;
	virtual void Update() override=0;
	virtual void Clean() override=0;
	virtual void InitRigidBody() override = 0;
	virtual b2Body* GetRigidBody() override = 0;
	virtual void TakeDamage(float damage) = 0;
	virtual void Die() = 0;

	//void SetAnimationState()
};
#endif /* defined (__ENEMY__) */