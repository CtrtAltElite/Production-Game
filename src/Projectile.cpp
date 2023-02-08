#include "Projectile.h"

Projectile::Projectile()
{
    
}

Projectile::~Projectile()
    =default;


void Projectile::SetVeloDamp(glm::vec2 veloDamp)
{
    m_veloDamp = veloDamp;
}

void Projectile::SetAngle(float angle)
{
    m_angle = angle;
}

void Projectile::SetPlayer(Player* player)
{
    m_pPlayer = player;
}

void Projectile::SetIsColliding(bool colliding)
{
    m_isColliding = colliding;
}

void Projectile::SetSpeed(float speed)
{
    m_speed = speed;
}

void Projectile::SetMaxSpeed(float maxSpeed)
{
    m_maxSpeed = maxSpeed;
}

glm::vec2 Projectile::GetVeloDamp()
{
    return m_veloDamp;
}

float Projectile::GetAngle() const
{
    return m_angle;
}

Player* Projectile::GetPlayer() const
{
    return m_pPlayer;
}

bool Projectile::GetIsColliding() const
{
    return m_isColliding;
}

float Projectile::GetSpeed() const
{
    return m_speed;
}

float Projectile::GetMaxSpeed() const
{
    return m_maxSpeed;
}
