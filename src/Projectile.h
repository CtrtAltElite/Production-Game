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
	void Draw() override;
	void Update() override;
	void Clean() override;
	void SetMaxSpeed(float maxSpeed) {m_maxSpeed = maxSpeed;}
	float GetMaxSpeed(){return m_maxSpeed;}
	void Start();
	void Move();
private:
	glm::vec2 veloDamp;
	float m_angle;
	Player* m_pPlayer;
	bool isColliding;
	float m_speed;
	float m_maxSpeed;
	glm::ivec2 m_mousepos;
	
};
#endif /* defined (__PROJECTILE__)*/