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
	void Draw() override =0;
	void Update() override =0;
	void Clean() override = 0; 
	virtual void Start() =0;
	virtual void Move() =0 ;

	
	void SetVeloDamp(glm::vec2 veloDamp);
	void SetAngle(float angle);
	void SetPlayer(Player* player);
	void SetIsColliding(bool colliding);
	void SetSpeed(float speed);
	void SetMaxSpeed(float maxSpeed);

	glm::vec2 GetVeloDamp();
	[[nodiscard]] float GetAngle() const;
	[[nodiscard]] Player* GetPlayer() const;
	[[nodiscard]] bool GetIsColliding() const;
	[[nodiscard]] float GetSpeed() const;
	[[nodiscard]] float GetMaxSpeed() const;

private:
	glm::vec2 m_veloDamp;
	float m_angle;
	Player* m_pPlayer;
	bool m_isColliding;
	float m_speed;
	float m_maxSpeed;
	
};
#endif /* defined (__PROJECTILE__)*/