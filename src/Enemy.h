#pragma once
#ifndef __ENEMY__
#define __ENEMY
#include "Sprite.h"
class Enemy : public Sprite
{
public:
	Enemy();
	virtual ~Enemy();

	// Life Cycle Methods
	void Draw() override = 0;
	void Update() override = 0;
	void Clean() override = 0;

	virtual void Move();


	void SetIsColliding(bool collide);
	void SetIsDead (bool dead);
	void SetHealth (float health);
	void SetSpeed (float speed);
	void SetMaxSpeed (float maxSpeed);
	void SetVeloDamp (glm::vec2 veloDamp);
	void SetScoreValue (float scoreValue);

	[[nodiscard]] float GetSpeed() const;
	[[nodiscard]] float GetMaxSpeed() const;
	[[nodiscard]] glm::vec2 GetVeloDamp();
	[[nodiscard]] bool GetIsColliding() const;
	[[nodiscard]] bool GetIsDead() const;
	[[nodiscard]] float GetHealth() const;
	[[nodiscard]] float GetScoreValue() const;
	

	
	//void SetAnimationState()
private:
	float m_Health;
	float m_Speed;
	float m_maxSpeed;
	bool m_isColliding;
	bool m_isDead;
	float m_scorevalue;
	glm::vec2 m_veloDamp;
};
#endif /* defined (__ENEMY__) */