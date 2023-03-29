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

	
	void SetIsDead (bool dead);
	void SetHealth (float health);
	void SetSpeed (float speed);
	void SetMaxSpeed (float maxSpeed);
	void SetVeloDamp (glm::vec2 veloDamp);
	void SetScoreValue (float scoreValue);
	void SetDeleteMe(bool deleteMe);
	void SetTargetPlayer(GameObject* targetPlayer);
	void SetFlipped(bool flip);
	void SetAttackDamage(float damage);
	virtual void TakeDamage(float damage);

	[[nodiscard]] float GetSpeed() const;
	[[nodiscard]] float GetMaxSpeed() const;
	[[nodiscard]] glm::vec2 GetVeloDamp();
	[[nodiscard]] bool GetIsDead() const;
	[[nodiscard]] float GetHealth() const;
	[[nodiscard]] float GetScoreValue() const;
	[[nodiscard]] bool GetDeleteMe() const;
	[[nodiscard]] GameObject* GetTargetPlayer() const;
	[[nodiscard]] bool GetFlipped();
	[[nodiscard]] float GetAttackDamage();

	
	//void SetAnimationState()
private:
	float m_Health;
	float m_Speed;
	float m_maxSpeed;
	bool m_isDead;
	bool m_deleteMe;
	bool m_flipped;
	float m_scorevalue;
	glm::vec2 m_veloDamp;
	GameObject* m_pTargetPlayer;
	float m_attackDamage;
	bool wanderFlip=true;
};

// Holds all the enemies in the scene and deals with the deletion
class EnemyPool : public DisplayObject
{
public:
	EnemyPool();

	// Lifecycle functions
	void Update() override;
	void Clean();
	void Draw() override;

	// Specific functions
	std::vector<Enemy*> GetPool();
	void Spawn(Enemy* enemyType);
	void UpdateTargetPlayer(GameObject* targetObject) const;

private:
	std::vector<Enemy*> m_pEnemies;
}; 
#endif /* defined (__ENEMY__) */