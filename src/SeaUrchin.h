#pragma once
#ifndef __SEA_URCHIN_H__
#define __SEA_URCHIN_H__

#include "Obstacle.h"
#include "Sprite.h"

class SeaUrchin : public Obstacle, public Sprite
{
public:
	SeaUrchin();
	void Draw() override;
	void Update() override;
	void Clean() override;
private:
	float randomDecreasingNumber;
};

#endif //!__SEA_URCHIN_H__