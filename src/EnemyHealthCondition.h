#pragma once
#ifndef __ENEMY_HEALTH_CONDITION_H__
#define __ENEMY_HEALTH_CONDITION_H__

#include "ConditionNode.h"

class EnemyHealthCondition : public ConditionNode
{
public:
	EnemyHealthCondition(Agent* agent = nullptr, bool healthy = false);

	virtual ~EnemyHealthCondition();

	// Getters and Setters
	void SetHealthy(bool state);

	virtual bool Condition() override;
private:
	bool m_isWithinCombatRange;
};

#endif // !__ENEMY_HEALTH_CONDITION_H__