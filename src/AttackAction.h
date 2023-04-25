#pragma once
#ifndef __ATTACKACTION_H__
#define __ATTACKACTION_H__

#include "ActionNode.h"

class AttackAction : public ActionNode
{
public:
	AttackAction(Agent* agent = nullptr);
	virtual ~AttackAction();

	virtual void Action() override;
private:

};

#endif //!__ATTACKACTION_H__