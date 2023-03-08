#pragma once
#ifndef __SCENE_STATE__
#define __SCENE_STATE__
enum class SceneState
{
	NO_SCENE = -1,
	START,
	LSP,// prolog pick
	LS1,// level 1 pick
	LS2, // level 2 pick
	LS3, // level 3 pick
	LSB, // Boss fight pick
	OPP, // opptions
	WHAT, // burning easter egg
	PLAY,
	/*
	PLAYP, // Play Prolong
	PLAY1, // Play 1
	PLAY2, // Play 2
	PLAY3, // Play 3
	PLAYB, // Play boss
	*/
	END,
	//END1, // the good ending
	//END2, // The Bad ending
	//END3, // the what ending
	PAUSE,
	//FAIL, // this is happaning a lot there is a t  you know for those who cant quite get it
	//WIN, //TBD 
	NUM_OF_SCENES
};
#endif /* defined (__SCENE_STATE__) */