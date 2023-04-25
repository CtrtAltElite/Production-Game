#pragma once
#ifndef __ENEMY_ANIMATION_STATE_H__
#define __ENEMY_ANIMATION_STATE_H__

enum class EnemyAnimationState
{
	ENEMY_IDLE_LEFT,
	ENEMY_IDLE_RIGHT,
	ENEMY_RUN_LEFT,
	ENEMY_RUN_RIGHT,
	ENEMY_RUN_UP,
	ENEMY_RUN_DOWN,
	ENEMY_DAMAGE,
	ENEMY_DEAD,
	NUM_OF_ANIM_STATES
};

#endif //!__ENEMY_ANIMATION_STATE_H__