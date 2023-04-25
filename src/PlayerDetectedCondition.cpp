#include "PlayerDetectedCondition.h"

PlayerDetectedCondition::PlayerDetectedCondition(Agent* agent, const bool playerDetected) : ConditionNode(agent)
{
	m_name = "Player Detected Condition";
	SetPlayerDetected(playerDetected);
}

PlayerDetectedCondition::~PlayerDetectedCondition()
= default;

void PlayerDetectedCondition::SetPlayerDetected(const bool state)
{
	m_detected = state;
}

bool PlayerDetectedCondition::GetDetected() const
{
	return m_detected;
}


bool PlayerDetectedCondition::Condition()
{
	return m_detected;
}
