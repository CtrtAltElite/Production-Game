#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include <box2d.h>

#include "Sprite.h"

class Player final : public Sprite
{
public:
	Player();
	~Player() override;

	// Life Cycle Methods
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;
	void InitRigidBody() override;
	b2Body*GetRigidBody() override;
	void MoveAtMouse();
private:
	bool isColliding;
	b2Body* m_rigidBody;
	float m_maxLinearVelo=0.0f; //doesnt work
};

#endif /* defined (__PLAYER__) */