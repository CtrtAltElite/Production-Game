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
	Projectile();
	virtual ~Projectile();
	// Life Cycle Methods
	virtual void Draw()=0;
	virtual void Update()=0;
	virtual void Clean() = 0; 
	virtual void Start() =0;
	virtual void Move() =0 ;

	
	void SetVeloDamp(glm::vec2 veloDamp);
	void SetAngle(float angle);
	void SetPlayer(Player* player);
	void SetIsColliding(bool colliding);
	void SetSpeed(float speed);
	void SetMaxSpeed(float maxSpeed);

	glm::vec2 GetVeloDamp();
	float GetAngle();
	Player* GetPlayer();
	bool GetIsColliding();
	float GetSpeed();
	float GetMaxSpeed();

private:
	glm::vec2 m_veloDamp;
	float m_angle;
	Player* m_pPlayer;
	bool m_isColliding;
	float m_speed;
	float m_maxSpeed;
	
};
#endif /* defined (__PROJECTILE__)*/