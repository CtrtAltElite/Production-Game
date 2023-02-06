#pragma once
#ifndef __PLANE__
#define __PLANE__

#include "Sprite.h"

class Plane final : public Sprite
{
public:
	Plane();
	~Plane() override;

	// Life Cycle Functions
	void Draw() override;
	void Update() override;
	void Clean() override;

private:
	void BuildAnimations();
};

#endif /* defined (__PLANE__) */
