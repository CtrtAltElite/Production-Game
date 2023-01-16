#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "PlayerAnimationState.h"
#include "Sprite.h"

class Player final : public Sprite
{
public:
	Player();
	~Player() override;

	// Life Cycle Methods
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;

	// setters
	void SetAnimationState(PlayerAnimationState new_state);
	float m_speed;
private:
	void BuildAnimations();

	PlayerAnimationState m_currentAnimationState;
	float m_maxvelo;
	float m_velodecay;
};

#endif /* defined (__PLAYER__) */