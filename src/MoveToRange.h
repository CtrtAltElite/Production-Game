#pragma once
#ifndef __MOVE_TO_RANGE_H__
#define __MOVE_TO_RANGE_H__

#include "ActionNode.h"

class MoveToRangeAction : public ActionNode
{
public:
	MoveToRangeAction(Agent* agent = nullptr);
	virtual ~MoveToRangeAction();

	virtual void Action() override;
private:

};

#endif //!__MOVE_TO_RANGE_H__