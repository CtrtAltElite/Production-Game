#include "Shark.h"

#include "Util.h"

void Shark::Draw()
{

}

void Shark::Update()
{

}

void Shark::Clean()
{
}

void Shark::TakeDamage(float damage)
{
	m_health -= damage;
	Util::Clamp(m_health, 0.0f, m_maxHealth);
	if (m_health == 0.0f)
		Die();
	
}

void Shark::Die()
{
	isDead = true;
}

void Shark::InitRigidBody()
{

}

b2Body* Shark::GetRigidBody()
{
	return m_rigidBody;
}
