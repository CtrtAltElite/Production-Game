#pragma once
#ifndef __ACTION_STATE__
#define __ACTION_STATE__
enum class ActionState
{
	NO_ACTION = -1,
	PATROL,
	ATTACK,
	MOVE_TO_LOS,
	MOVE_TO_PLAYER,
	MOVE_TO_RANGE,
	FLEE,
	WAIT_BEHIND_COVER,
	MOVE_TO_COVER,
};
#endif /* defined (__ACTION_STATE__)*/