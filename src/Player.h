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

	void MoveAtMouse();
	void LookAtMouse();

	// setters
	void SetAnimationState(PlayerAnimationState new_state);
	void SetMaxSpeed (float maxSpeed);
	void SetFlipped(bool flipped);
	void SetScore(float score);
	void SetKillcount(int killcount);
	
	float GetMaxSpeed() const;
	bool GetFlipped() const;
	float GetScore();
	int GetKillcount();

private:
	void BuildAnimations();
	float m_speed;
	float m_maxSpeed;
	glm::vec2 m_mousePos;
	float animVelo;
	float animVeloDamp;
	bool m_flipped;
	float m_score;
	int m_killCount;

	PlayerAnimationState m_currentAnimationState;
};

#endif /* defined (__PLAYER__) */