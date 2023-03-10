#pragma once
#ifndef __RIGID_BODY__
#define __RIGID_BODY__
#include <vector>
#include <glm/vec2.hpp>

struct RigidBody
{
	float mass = 1.0f;
	glm::vec2 bounds;

	glm::vec2 velocity;
	glm::vec2 acceleration;
	glm::vec2 velocityDampening;
	float angularVelocity;
	float angularVelocityDampening;
	float angularAcceleration;
	bool isColliding = false;
	std::vector<RigidBody*> currentCollisions;
};
#endif /* defined (__RIGID_BODY__) */