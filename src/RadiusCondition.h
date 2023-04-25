#pragma once
#ifndef __RADIUS_CONDITION_H__
#define __RADIUS_CONDITION_H__

#include "ConditionNode.h"

class RadiusCondition : public ConditionNode
{
public:
	RadiusCondition(Agent* agent = nullptr, bool within_radius = false);

	virtual ~RadiusCondition();

	// Getters and Setters
	void SetIsWithinRadius(bool state);

	virtual bool Condition() override;
private:
	bool m_isWithinRadius;
};

#endif //!__RADIUS_CONDITION_H__