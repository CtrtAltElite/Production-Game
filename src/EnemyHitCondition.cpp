#include "EnemyHitCondition.h"

EnemyHitCondition::EnemyHitCondition(Agent* agent, const bool hit) : ConditionNode(agent)
{
	m_name = "Enemy Hit Condition";
	SetHit(hit);
}

EnemyHitCondition::~EnemyHitCondition()
= default;

void EnemyHitCondition::SetHit(const bool state)
{
	m_hit = state;
}

bool EnemyHitCondition::GetHit() const
{
	return m_hit;
}

bool EnemyHitCondition::Condition()
{
	return m_hit;
}
