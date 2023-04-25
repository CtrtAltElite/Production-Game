#pragma once
#ifndef __ENEMY_HIT_CONDITION_H__
#define __ENEMY_HIT_CONDITION_H__

#include "ConditionNode.h"

class EnemyHitCondition : public ConditionNode
{
public:
	EnemyHitCondition(Agent* agent = nullptr, bool hit = false);

	virtual ~EnemyHitCondition();

	// Getters and Setters
	void SetHit(bool state);
	bool GetHit() const;

	virtual bool Condition() override;
private:
	bool m_hit;
};

#endif // !_RANGED_COMBAT_CONDITION_H__