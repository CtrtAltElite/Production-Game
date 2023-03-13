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
	void Collision();

	void MoveAtMouse();
	void LookAtMouse();

	// setters
	void SetAnimationState(PlayerAnimationState new_state);
	void SetMaxSpeed (float maxSpeed);
	void SetFlipped(bool flipped);
	void SetScore(float score);
	void SetKillcount(int killcount);
	void SetHealth(float health);
	void SetIsDead (bool isDead);
	void TakeDamage (float damage);


	[[nodiscard]] float GetMaxSpeed() const;
	[[nodiscard]] bool GetFlipped() const;
	float GetScore();
	int GetKillcount();
	float GetHealth();
	bool GetIsDead();

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
	float m_Health;
	bool m_isDead;

	PlayerAnimationState m_currentAnimationState;
};

#endif /* defined (__PLAYER__) */