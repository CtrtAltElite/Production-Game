#pragma once
#ifndef __TARGET__
#define __TARGET__

#include "DisplayObject.h"

class Target final : public DisplayObject {
public:
	Target();
	~Target() override;

	// Inherited via GameObject
	void Draw() override;
	void Update() override;
	void Clean() override;

private:
	void Move();
	void CheckBounds();
	void Reset();
};


#endif /* defined (__TARGET__) */