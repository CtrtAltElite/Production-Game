#include "Agent.h"

#include "Util.h"
#include "CollisionManager.h"

Agent::Agent()
{
	// initialize whisker colour
	m_lineColour[0] = glm::vec4(0, 1, 0, 1); // left left line colour
	m_lineColour[1] = glm::vec4(0, 1, 0, 1); // left line colour
	m_lineColour[2] = glm::vec4(0, 1, 0, 1); // middle line colour
	m_lineColour[3] = glm::vec4(0, 1, 0, 1); // right line colour
	m_lineColour[4] = glm::vec4(0, 1, 0, 1); // right right line colour

	// initialize the whisker collision booleans
	m_collisionWhiskers[0] = false;
	m_collisionWhiskers[1] = false;
	m_collisionWhiskers[2] = false;
	m_collisionWhiskers[3] = false;
	m_collisionWhiskers[4] = false;

	m_whiskerAngle = 45;
}

Agent::~Agent()
= default;

glm::vec2 Agent::GetTargetPosition() const
{
	return m_targetPosition;
}

glm::vec2 Agent::GetCurrentDirection() const
{
	return m_currentDirection;
}

float Agent::GetLOSDistance() const
{
	return m_LOSDistance;
}

bool Agent::HasLOS() const
{
	return m_hasLOS;
}

float Agent::GetCurrentHeading() const
{
	return m_currentHeading;
}

glm::vec4 Agent::GetLOSColour() const
{
	return m_LOSColour;
}

glm::vec2 Agent::GetLeftLeftLOSEndPoint() const
{
	return m_leftLeftLOSEndPoint;
}

glm::vec2 Agent::GetRightRightLOSEndPoint() const
{
	return m_rightRightLOSEndPoint;
}

EnemyType Agent::GetEnemyType() const
{
	return m_type;
}

EnemyAnimationState Agent::GetAnimationState() const
{
	return m_animState;
}


void Agent::SetLeftLeftLOSEndPoint(const glm::vec2 point)
{
	m_leftLeftLOSEndPoint = point;
}

void Agent::SetRightRightLOSEndPoint(const glm::vec2 point)
{
	m_rightRightLOSEndPoint = point;
}

glm::vec2 Agent::GetLeftLOSEndPoint() const
{
	return m_leftLOSEndPoint;
}

glm::vec2 Agent::GetMiddleLOSEndPoint() const
{
	return m_middleLOSEndPoint;
}

glm::vec2 Agent::GetRightLOSEndPoint() const
{
	return m_rightLOSEndPoint;
}

bool* Agent::GetCollisionWhiskers()
{
	return m_collisionWhiskers;
}

glm::vec4 Agent::GetLineColour(const int index) const
{
	return m_lineColour[index];
}

float Agent::GetWhiskerAngle() const
{
	return m_whiskerAngle;
}

ActionState Agent::GetActionState() const
{
	return m_state;
}

void Agent::SetActionState(const ActionState state)
{
	m_state = state;
}

void Agent::SetAnimationState(EnemyAnimationState state)
{
	m_animState = state;
}

void Agent::SetLeftLOSEndPoint(const glm::vec2 point)
{
	m_leftLOSEndPoint = point;
}

void Agent::SetMiddleLOSEndPoint(const glm::vec2 point)
{
	m_middleLOSEndPoint = point;
}

void Agent::SetRightLOSEndPoint(const glm::vec2 point)
{
	m_rightLOSEndPoint = point;
}

void Agent::SetEnemyType(EnemyType type)
{
	m_type = type;
}

void Agent::SetLineColour(const int index, const glm::vec4 colour)
{
	m_lineColour[index] = colour;
}

void Agent::SetWhiskerAngle(const float angle)
{
	m_whiskerAngle = angle;
}

void Agent::UpdateWhiskers(const float angle)
{
	m_whiskerAngle = angle;

	// center / middle whisker
	SetMiddleLOSEndPoint(GetTransform()->position + GetCurrentDirection() * GetLOSDistance());

	// Left Left
	float x = sin((GetCurrentHeading() - 75.0f + 90.0f) * Util::Deg2Rad);
	float y = cos((GetCurrentHeading() - 75.0f + 90.0f) * Util::Deg2Rad);
	SetLeftLeftLOSEndPoint(GetTransform()->position + glm::vec2(x, -y) * GetLOSDistance() * 0.75f);

	// left whisker
	x = sin((GetCurrentHeading() - m_whiskerAngle + 90.0f) * Util::Deg2Rad);
	y = cos((GetCurrentHeading() - m_whiskerAngle + 90.0f) * Util::Deg2Rad);
	SetLeftLOSEndPoint(GetTransform()->position + glm::vec2(x, -y) * GetLOSDistance() * 0.75f);

	// right whisker
	x = sin((GetCurrentHeading() + m_whiskerAngle + 90.0f) * Util::Deg2Rad);
	y = cos((GetCurrentHeading() + m_whiskerAngle + 90.0f) * Util::Deg2Rad);
	SetRightLOSEndPoint(GetTransform()->position + glm::vec2(x, -y) * GetLOSDistance() * 0.75f);

	// right right 
	x = sin((GetCurrentHeading() + 75.0f + 90.0f) * Util::Deg2Rad);
	y = cos((GetCurrentHeading() + 75.0f + 90.0f) * Util::Deg2Rad);
	SetRightRightLOSEndPoint(GetTransform()->position + glm::vec2(x, -y) * GetLOSDistance() * 0.75f);
}

bool Agent::CheckAgentLOSToTarget(DisplayObject* target_object, const std::vector<Obstacle*>& obstacles)
{
	bool has_LOS = false; // default - No LOS
	SetHasLOS(has_LOS);

	const auto target_direction = target_object->GetTransform()->position - GetTransform()->position;
	const auto normalized_direction = Util::Normalize(target_direction); // Points to the target (Unit Vector)
	SetMiddleLOSEndPoint(GetTransform()->position + normalized_direction * GetLOSDistance());

	// if ship to target distance is less than or equal to the LOS Distance (Range)
	const auto agent_to_range = Util::GetClosestEdge(GetTransform()->position, target_object);
	if (agent_to_range <= GetLOSDistance())
	{
		// we are in within LOS Distance 
		std::vector<DisplayObject*> contact_list;
		for (const auto obstacle : obstacles)
		{
			const auto agent_to_object_distance = Util::GetClosestEdge(GetTransform()->position, obstacle);
			if (agent_to_object_distance > agent_to_range) { continue; }
			if ((obstacle->GetType() != GameObjectType::AGENT)
				&& (obstacle->GetType() != GameObjectType::PATH_NODE)
				&& (obstacle->GetType() != GameObjectType::TARGET))
			{
				 contact_list.push_back(obstacle); // target is out of range

			}
		}

		has_LOS = CollisionManager::LOSCheck(this, GetMiddleLOSEndPoint(), contact_list, target_object);

		/*const auto LOSColour = (target_object->GetType() == GameObjectType::AGENT) ? glm::vec4(0, 0, 1, 1) : glm::vec4(0, 1, 0, 1);
		agent->SetHasLOS(has_LOS, LOSColour);*/
	}

	SetHasLOS(has_LOS);
	return has_LOS;
}


void Agent::SetTargetPosition(const glm::vec2 new_position)
{
	m_targetPosition = new_position;
}

void Agent::SetCurrentDirection(const glm::vec2 new_direction)
{
	m_currentDirection = new_direction;
}

void Agent::SetLOSDistance(const float distance)
{
	m_LOSDistance = distance;
}

void Agent::SetHasLOS(const bool state)
{
	m_hasLOS = state;
	m_LOSColour = (m_hasLOS) ? glm::vec4(0, 1, 0, 1) : glm::vec4(1, 0, 0, 1);
}

void Agent::SetHasLOS(const bool state, glm::vec4 colour)
{
	m_hasLOS = state;
	m_LOSColour = (m_hasLOS) ? colour : glm::vec4(1, 0, 0, 1);
}

void Agent::SetCurrentHeading(const float heading)
{
	m_currentHeading = heading;
	ChangeDirection();
}

void Agent::SetLOSColour(const glm::vec4 colour)
{
	m_LOSColour = colour;
}



void Agent::ChangeDirection()
{
	const auto x = cos(m_currentHeading * Util::Deg2Rad);
	const auto y = sin(m_currentHeading * Util::Deg2Rad);
	m_currentDirection = glm::vec2(x, y);
}
