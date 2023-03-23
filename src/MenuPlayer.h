#pragma once
#ifndef __MENU_PLAYER_H__
#define __MENU_PLAYER_H__

#include "Sprite.h"

class MenuPlayer final : public Sprite
{
	public:
	// Constructor + Destructor
	MenuPlayer();
	~MenuPlayer() override;

	// Life Cycle Methods
	void Draw() override;
	void Update() override;
	void Clean() override;

	// Player movement functions
	void Move();

private:

};

#endif //!__MENU_PLAYER_H__