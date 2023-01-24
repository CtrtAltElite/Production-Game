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
	void InitRigidBody() override;
	b2Body* GetRigidBody() override;

	// setters
	
private:
	b2Body* m_rigidBody;
	
};

#endif /* defined (__BACKGROUND__) */
