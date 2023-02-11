#include "Enemy.h"

#include "Game.h"
#include "Util.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
=default;

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

void Enemy::SetScoreValue(float scoreValue)
{
    m_scorevalue = scoreValue;
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

float Enemy::GetScoreValue() const
{
    return m_scorevalue;
}

void Enemy::Move()
{
    const float dt = Game::Instance().GetDeltaTime();
    const glm::vec2 initial_position = GetTransform()->position;
    const glm::vec2 velocity_term = GetRigidBody()->velocity * dt;
    const glm::vec2 acceleration_term = GetRigidBody()->acceleration * 0.5f;
    const glm::vec2 final_position = initial_position + velocity_term + acceleration_term;
    GetTransform()->position = final_position;
    GetRigidBody()->velocity += GetRigidBody()->acceleration;
    GetRigidBody()->velocity = Util::Clamp(GetRigidBody()->velocity,GetMaxSpeed());
    const float initial_rotation = GetTransform()->rotation.r;
    const float angularVelocity_term = GetRigidBody()->angularVelocity * dt;
    const float angularAcceleration_term = GetRigidBody()->angularAcceleration * 0.5f;
    const float final_rotation = initial_rotation + angularVelocity_term + angularAcceleration_term;
    GetTransform()->rotation.r = final_rotation;
    GetRigidBody()->angularVelocity += GetRigidBody()->angularAcceleration;
    GetRigidBody()->velocity*=GetRigidBody()->velocityDampening;
    GetRigidBody()->angularVelocity*=GetRigidBody()->angularVelocityDampening;
    CollisionManager::RotateAABB(this, this->GetTransform()->rotation.r*Util::Rad2Deg);
}

