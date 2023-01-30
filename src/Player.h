#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include <box2d.h>
#include <glm/vec2.hpp>

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
	void RotateToMouse();
private:
	b2Vec2 m_mousePos;
	float m_angleToMouse;
	b2Vec2 m_lookTarget;
	bool m_isColliding=false;
	b2Body* m_rigidBody;
	float m_speed = 5000000.0f;
};

#endif /* defined (__PLAYER__) */