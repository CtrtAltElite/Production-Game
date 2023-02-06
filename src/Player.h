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
	void Move();

	// setters
	void SetAnimationState(PlayerAnimationState new_state);
	void MoveAtMouse();
	void LookAtMouse();
	void SetMaxSpeed (float maxSpeed) {m_maxSpeed = maxSpeed;}

	float GetMaxSpeed(){return m_maxSpeed;}

private:
	void BuildAnimations();
	float m_maxSpeed = 100.0f;
	glm::ivec2 m_mousePos;

	PlayerAnimationState m_currentAnimationState;
};

#endif /* defined (__PLAYER__) */