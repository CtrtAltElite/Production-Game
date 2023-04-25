#pragma once
#ifndef _RANGED_COMBAT_CONDITION_H__
#define _RANGED_COMBAT_CONDITION_H__

#include "ConditionNode.h"

class RangedCombatCondition : public ConditionNode
{
public:
	RangedCombatCondition(Agent* agent = nullptr, bool within_combat_range = false);

	virtual ~RangedCombatCondition();

	// Getters and Setters
	void SetIsWithinCombatRange(bool state);

	virtual bool Condition() override;
private:
	bool m_isWithinCombatRange;
};

#endif // !_RANGED_COMBAT_CONDITION_H__