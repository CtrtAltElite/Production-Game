#pragma once
#ifndef __SCENE_STATE__
#define __SCENE_STATE__
enum class SceneState
{
	NO_SCENE,
	START,
	LEVEL_SELECT,
	TUTORIAL,// tutorial pick
	LEVEL_ONE,// level 1 pick
	LEVEL_TWO, // level 2 pick
	LEVEL_THREE, // level 3 pick
	BOSS_LEVEL, // Boss fight pick
	PLAY,
	PAUSE,
	GAME_OVER,
	END,
	NUM_OF_SCENES
};
#endif /* defined (__SCENE_STATE__) */