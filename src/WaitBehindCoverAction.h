#pragma once
#ifndef __WAIT_BEHIND_COVER_ACTION_H__
#define __WAIT_BEHIND_COVER_ACTION_H__

#include "ActionNode.h"

class WaitBehindCoverAction : public ActionNode
{
public:
	WaitBehindCoverAction(Agent* agent = nullptr);
	virtual ~WaitBehindCoverAction();

	virtual void Action() override;
private:

};

#endif //!__WAIT_BEHIND_COVER_ACTION_H__