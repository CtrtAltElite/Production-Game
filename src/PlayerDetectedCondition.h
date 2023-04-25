#pragma once
#ifndef __PLAYER_DETECTED_CONDITION_H__
#define __PLAYER_DETECTED_CONDITION_H__

#include "ConditionNode.h"

class PlayerDetectedCondition : public ConditionNode
{
public:
	PlayerDetectedCondition(Agent* agent = nullptr, bool playerDetected = false);

	virtual ~PlayerDetectedCondition();

	// Getters and Setters
	void SetPlayerDetected(bool state);
	bool GetDetected() const;

	virtual bool Condition() override;
private:
	bool m_detected;
};

#endif // !__PLAYER_DETECTED_CONDITION_H__