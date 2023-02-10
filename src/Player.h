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
	void Draw() override;
	void Update() override;
	void Clean() override;
	void Move();

	// setters
	void SetAnimationState(PlayerAnimationState new_state);
	void MoveAtMouse();
	void LookAtMouse();
	void SetMaxSpeed (float maxSpeed) {m_maxSpeed = maxSpeed;}

	float GetMaxSpeed() const {return m_maxSpeed;}

	void SetFlipped(bool flipped){m_flipped = flipped;}
	bool GetFlipped() const {return m_flipped;}

private:
	void BuildAnimations();
	float m_speed;
	float m_maxSpeed;
	glm::vec2 m_mousePos;
	float animVelo;
	float animVeloDamp;
	bool m_flipped;

	PlayerAnimationState m_currentAnimationState;
};

#endif /* defined (__PLAYER__) */