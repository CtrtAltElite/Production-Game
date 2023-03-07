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

void Enemy::SetDeleteMe(bool deleteMe)
{
    m_deleteMe = deleteMe;
}

void Enemy::SetTargetPlayer(DisplayObject* targetPlayer)
{
    m_pTargetPlayer = targetPlayer;
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

bool Enemy::GetDeleteMe() const
{
    return m_deleteMe;
}

EnemyPool::EnemyPool()
{ }

void EnemyPool::Update()
{
    for (int i = 0; i < m_enemies.size(); i++)
    {
	    if (m_enemies[i]->GetDeleteMe() == true)
	    {
            delete m_enemies[i];
            m_enemies[i] = nullptr;
            m_enemies.erase(i + m_enemies.begin());
            m_enemies.shrink_to_fit();
	    } else
	    {
            m_enemies[i]->Update();
	    }
    }
}

void EnemyPool::Clean()
{
}

void EnemyPool::Draw()
{
    for (Enemy* enemy : m_enemies)
    {
        enemy->Draw(); 
    }
}

std::vector<Enemy*> EnemyPool::GetPool()
{
    return m_enemies;
}

void EnemyPool::Spawn(Enemy* enemyType)
{
    m_enemies.push_back(enemyType);
}

void EnemyPool::UpdateTargetPlayer(DisplayObject* targetObject) const
{
    for (auto enemy : m_enemies)
    {
        enemy->SetTargetPlayer(targetObject);
    }
}

void Enemy::Move()
{
    if (m_pTargetPlayer != nullptr)
    {
        // Getting initial instances of position, velocity, and target position
        const float dt = Game::Instance().GetDeltaTime();
        glm::vec2 plr_position = GetTransform()->position;
        glm::vec2 new_velocity;
        glm::vec2 steering;
        glm::vec2 target_position = m_pTargetPlayer->GetTransform()->position;

        // Something is making this equal glm::vec2(-nan,-nan); and idk what



        // Getting length of veloicty vector (controls how much it moves via length between target and player) 
        new_velocity = Util::Normalize(target_position - plr_position) * GetMaxSpeed();


        std::cout << Util::Normalize(target_position - plr_position).x * GetSpeed() << " " << Util::Normalize(target_position - plr_position).y << std::endl;


        // Adding steering forces so we can rotate user in the right direction, influences character movement
        steering = new_velocity - GetRigidBody()->velocity;



        // Adding forces to the player (specifically the velocity force)
        // Should make enemy smoothly head towards their target taking into account mass
        //steering = std::min(steering, ));
        steering = steering / GetRigidBody()->mass;


        GetRigidBody()->velocity = GetRigidBody()->velocity + steering;


        // Adding velocity to position via Euler integration
        GetTransform()->position = plr_position + GetRigidBody()->velocity;

        //std::cout << GetTransform()->position.x << " " << GetTransform()->position.y << std::endl;
        /* Will fix this tonight, making seek work for shark*/
        /*const glm::vec2 velocity_term = GetRigidBody()->velocity * dt;
        const glm::vec2 acceleration_term = GetRigidBody()->acceleration * 0.5f;
        const glm::vec2 final_position = initial_position + velocity_term + acceleration_term;
        GetTransform()->position = final_position;
        GetRigidBody()->velocity += GetRigidBody()->acceleration;
        GetRigidBody()->velocity = Util::Clamp(GetRigidBody()->velocity, GetMaxSpeed());
        const float initial_rotation = GetTransform()->rotation.r;
        const float angularVelocity_term = GetRigidBody()->angularVelocity * dt;
        const float angularAcceleration_term = GetRigidBody()->angularAcceleration * 0.5f;
        const float final_rotation = initial_rotation + angularVelocity_term + angularAcceleration_term;
        GetTransform()->rotation.r = final_rotation;
        GetRigidBody()->angularVelocity += GetRigidBody()->angularAcceleration;
        GetRigidBody()->velocity *= GetRigidBody()->velocityDampening;
        GetRigidBody()->angularVelocity *= GetRigidBody()->angularVelocityDampening;*/
        CollisionManager::RotateAABB(this, this->GetTransform()->rotation.r * Util::Rad2Deg);
    }
}

