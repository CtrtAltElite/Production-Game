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
	void Draw() override = 0;
	void Update() override = 0;
	void Clean() override = 0;

	void SetIsColliding(bool collide);
	void SetIsDead (bool dead);
	void SetHealth (float health);
	void SetSpeed (float speed);
	void SetMaxSpeed (float maxSpeed);
	void SetVeloDamp (glm::vec2 veloDamp);
	
	float GetSpeed() const;
	float GetMaxSpeed() const;
	glm::vec2 GetVeloDamp();
	bool GetIsColliding() const;
	bool GetIsDead() const;
	float GetHealth() const;

	
	//void SetAnimationState()
private:
	float m_Health;
	float m_Speed;
	float m_maxSpeed;
	bool m_isColliding;
	bool m_isDead;
	glm::vec2 m_veloDamp;
	void BuildAnimations();
};
#endif /* defined (__ENEMY__) */