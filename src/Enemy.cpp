#include "Enemy.h"

void Enemy::SetIsColliding(bool collide)
{
    m_isColliding = collide;
}

void Enemy::SetIsDead(bool dead)
{
    m_isDead = dead;
}

void Enemy::SetHealth(float health)
{
    m_Health = health;
}

void Enemy::SetSpeed(float speed)
{
    m_Speed = speed;
}

void Enemy::SetMaxSpeed(float maxSpeed)
{
    m_maxSpeed = maxSpeed;
}

void Enemy::SetVeloDamp(glm::vec2 veloDamp)
{
    m_veloDamp = veloDamp;
}

float Enemy::GetSpeed() const
{
    return m_Speed;
}

float Enemy::GetMaxSpeed() const
{
    return m_maxSpeed;
}

glm::vec2 Enemy::GetVeloDamp()
{
    return m_veloDamp;
}

bool Enemy::GetIsColliding() const
{
    return m_isColliding;
}

bool Enemy::GetIsDead() const
{
    return m_isDead;
}

float Enemy::GetHealth() const
{
    return m_Health;
}
