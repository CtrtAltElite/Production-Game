#pragma once
#ifndef __PATROLACTION_H__
#define __PATROLACTION_H__

#include "ActionNode.h"

class PatrolAction : public ActionNode
{
public:
	PatrolAction(Agent* agent = nullptr);
	virtual ~PatrolAction();

	virtual void Action() override;
private:

};

#endif //!__PATROLACTION_H__