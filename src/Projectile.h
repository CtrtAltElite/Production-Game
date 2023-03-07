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
	virtual void Move();
	
	
	void SetVeloDamp(glm::vec2 veloDamp);
	void SetPlayer(Player* player);
	void SetSpeed(float speed);
	void SetMaxSpeed(float maxSpeed);
	void SetDeleteMe(bool deleteMe);
	void SetProjectileSource(GameObject* source);
	void SetDeleteBuffer(float buffer);
	void SetDamage(float damage);
	void SetStartTime (Uint32 startTime);
	

	

	glm::vec2 GetVeloDamp();
	[[nodiscard]] Player* GetPlayer() const;
	[[nodiscard]] float GetSpeed() const;
	[[nodiscard]] float GetMaxSpeed() const;
	[[nodiscard]] bool GetDeleteMe() const;
	[[nodiscard]] GameObject* GetProjectileSource() const;
	[[nodiscard]] float GetDeleteBuffer() const;
	[[nodiscard]] float GetDamage() const;
	[[nodiscard]] Uint32 GetStartTime() const;
	

private:
	GameObject* m_pProjectileSource;
	glm::vec2 m_veloDamp;
	Player* m_pPlayer;
	float m_damage;
	float m_speed;
	float m_maxSpeed;
	bool m_deleteMe;
	float m_OffScreenDeleteBuffer;
	Uint32 m_startTime;
	
};
#endif /* defined (__PROJECTILE__)*/