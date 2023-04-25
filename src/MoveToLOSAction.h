#pragma once
#ifndef __MOVETOLOSACTION_H__
#define __MOVETOLOSACTION_H__

#include "ActionNode.h"

class MoveToLOSAction : public ActionNode
{
public:
	MoveToLOSAction(Agent* agent = nullptr);
	virtual ~MoveToLOSAction();

	virtual void Action() override;
private:

};

#endif //!__MOVETOLOSACTION_H__