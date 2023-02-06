#pragma once
#ifndef __PROJECTILE__
#define __PROJECTILE__

#include <glm/vec2.hpp>
#include <glm/detail/func_common.hpp>

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
	void SetMaxSpeed(float maxSpeed) {m_maxSpeed = maxSpeed;}
	float GetMaxSpeed(){return m_maxSpeed;}
	void Start();
	void Move();
private:
	float m_angle;
	Player* m_pPlayer;
	bool isColliding;
	float m_maxSpeed = 200.0f;
	glm::ivec2 m_mousepos;
	
};
#endif /* defined (__PROJECTILE__)*/