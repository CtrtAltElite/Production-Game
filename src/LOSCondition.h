#pragma once
#ifndef __LOS_CONDITION_H__
#define __LOS_CONDITION_H__

#include "ConditionNode.h"

class LOSCondition : public ConditionNode
{
public:
	LOSCondition(Agent* agent = nullptr);

	virtual ~LOSCondition();

	virtual bool Condition() override;
};

#endif // !__LOS_CONDITION_H__