#pragma once
#ifndef __ENEMY__
#define __ENEMY
#include "Sprite.h"
class Enemy final : public DisplayObject
{
public:
	Enemy();
	virtual ~Enemy();

	// Life Cycle Methods
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;

	//void SetAnimationState()
private:
	void BuildAnimations();
};
#endif /* defined (__ENEMY__) */