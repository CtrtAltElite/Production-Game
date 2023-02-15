#include "Projectile.h"

#include "Game.h"
#include "Util.h"

Projectile::Projectile()
{
    SetStartTime(SDL_GetTicks());
}
Projectile::~Projectile()
    =default;


void Projectile::SetVeloDamp(glm::vec2 veloDamp)
{
    GetRigidBody()->velocityDampening = veloDamp;
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

void Projectile::SetDeleteMe(bool deleteMe)
{
    m_deleteMe = deleteMe;
}

void Projectile::SetProjectileSource(GameObject* source)
{
    m_pProjectileSource = source;
}

void Projectile::SetDeleteBuffer(float buffer)
{
    m_OffScreenDeleteBuffer = buffer;
}

void Projectile::SetDamage(float damage)
{
    m_damage = damage;
}

void Projectile::SetStartTime(Uint32 startTime)
{
    m_startTime = startTime;
}

Uint32 Projectile::GetStartTime() const
{
    return m_startTime;
}

glm::vec2 Projectile::GetVeloDamp()
{
   return GetRigidBody()->velocityDampening;
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

bool Projectile::GetDeleteMe() const
{
    return m_deleteMe;
}

GameObject* Projectile::GetProjectileSource() const
{
    return m_pProjectileSource;
}

float Projectile::GetDeleteBuffer() const
{
    return m_OffScreenDeleteBuffer;
}

float Projectile::GetDamage() const
{
    return m_damage;
}


void Projectile::Move()
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
    //GetRigidBody()->velocity*=GetRigidBody()->velocityDampening;
    //GetRigidBody()->angularVelocity*=GetRigidBody()->angularVelocityDampening;
   //CollisionManager::RotateAABB(this, this->GetTransform()->rotation.r*Util::Rad2Deg); DOESNT LIKE THIS FOR SOME REASON
}

void Projectile::CheckBounds()
{
    if (GetTransform()->position.x<0-GetDeleteBuffer()||
        GetTransform()->position.y<0-GetDeleteBuffer()||
        GetTransform()->position.x>Config::SCREEN_WIDTH+GetDeleteBuffer()||
        GetTransform()->position.y>Config::SCREEN_HEIGHT+GetDeleteBuffer())
    {
        SetDeleteMe(true);
    }
}

