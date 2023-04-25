#pragma once
#ifndef __CLOSE_COMBAT_CONDITION_H__
#define __CLOSE_COMBAT_CONDITION_H__

#include "ConditionNode.h"

class CloseCombatCondition : public ConditionNode
{
public:
	CloseCombatCondition(Agent* agent = nullptr, bool within_combat_range = false);

	virtual ~CloseCombatCondition();

	// Getters and Setters
	void SetIsWithinCombatRange(bool state);

	virtual bool Condition() override;
private:
	bool m_isWithinCombatRange;
};

#endif // !__CLOSE_COMBAT_CONDITION_H__