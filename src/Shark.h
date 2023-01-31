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
private:
	b2Body* m_rigidBody;
	float m_health = 100.0f;
	float m_maxHealth = 100.0f;
	bool isDead = false;
};
