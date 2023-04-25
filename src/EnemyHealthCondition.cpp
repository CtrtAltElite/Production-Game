#include "EnemyHealthCondition.h"


EnemyHealthCondition::EnemyHealthCondition(Agent* agent, bool healthy) : ConditionNode(agent)
{
	m_name = "Enemy Health Condition";
	SetHealthy(healthy);
}

EnemyHealthCondition::~EnemyHealthCondition()
= default;

void EnemyHealthCondition::SetHealthy(const bool state)
{
	m_isWithinCombatRange = state;
}

bool EnemyHealthCondition::Condition()
{
	return m_isWithinCombatRange;
}
