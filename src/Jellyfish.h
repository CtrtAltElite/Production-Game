#pragma once
#ifndef __JELLYFISH_H__
#define __JELLYFISH_H__

#include "Obstacle.h"
#include "Sprite.h"

class Jellyfish : public Obstacle, public Sprite
{
public:
	Jellyfish();
	void Draw() override;
	void Update() override;
	void Clean() override;

private:
	float animVelo;
};

#endif //!__JELLYFISH_H__