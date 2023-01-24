#pragma once
#ifndef __OBSTACLE__
#define __OBSTACLE__
#include "DisplayObject.h"

class Obstacle final : public DisplayObject
{
public:
	// constructors
	Obstacle();
	
	// destructor
	~Obstacle() override;
	
	// life cycle functions
	void Draw() override;
	void Update() override;
	void Clean() override;
	void InitRigidBody(b2Vec2 position);
private:
	b2Body* m_rigidBody;
	
};

#endif /* defined (__OBSTACLE__) */