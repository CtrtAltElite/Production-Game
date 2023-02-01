#pragma once
#ifndef __BACKGROUND__
#define __BACKGROUND__

#include "DisplayObject.h"

class Background final : public DisplayObject
{
public:
	Background();
	~Background() override;

	// Life Cycle Methods
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;
	// setters
	
private:
	
	
};

#endif /* defined (__BACKGROUND__) */
