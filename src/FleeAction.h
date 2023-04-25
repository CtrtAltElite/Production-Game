#pragma once
#ifndef __FLEE_ACTION_H__
#define __FLEE_ACTION_H__

#include "ActionNode.h"

class FleeAction : public ActionNode
{
public:
	FleeAction(Agent* agent = nullptr);
	virtual ~FleeAction();

	virtual void Action() override;
private:

};

#endif //!__FLEE_ACTION_H__