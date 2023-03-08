#pragma once
#ifndef __STINGRAY_H__
#define __STINGRAY_H__

#include "Enemy.h"
#include "Obstacle.h"

class Stingray final : public Obstacle, public Enemy
{
public:
	Stingray();
	void Draw() override;
	void Update() override;
	void Clean() override;


private:
	float animVelo;
};


#endif //!__STINGRAY_H__
