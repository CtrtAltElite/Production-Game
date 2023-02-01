#pragma once
#ifndef __PROJECTILE__
#define __PROJECTILE__

#include <glm/vec2.hpp>

#include "Player.h"
#include "Sprite.h"

class Projectile : public Sprite
{
public:
	Projectile(Player* player);
	// Life Cycle Methods
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;
	void InitRigidBody()override;
	b2Body* GetRigidBody() override;
	void Start();
private:
	int deleteBuffer = 200.0f;
	float m_damage;
	float m_angle;
	b2Vec2 m_vector;
	b2Body* m_rigidBody;
	Player* m_player;
	bool m_deleteMe = false;
	float m_speed;
};
#endif /* defined (__PROJECTILE__)*/