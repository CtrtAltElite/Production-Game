#pragma once
#include "Enemy.h"

class Shark : public Enemy 
{
public:
	Shark();
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;
	virtual void TakeDamage(float damage) override;
	virtual void Die() override;
	virtual void InitRigidBody() override;
	virtual b2Body* GetRigidBody() override;
	virtual void ChangeDirection(float heading);
	virtual void ChangeDirection(b2Vec2 direction);
	virtual void Move();
	virtual void LookTowardsPlayer(b2Vec2 player_position);

	b2Vec2 GetDirection();
private:
	b2Body* m_rigidBody;
	float m_health = 100.0f;
	float m_maxHealth = 100.0f;
	bool isDead = false;
	b2Vec2 m_currentDirection;
};
