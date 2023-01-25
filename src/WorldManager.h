#pragma once
#include <vector>

#include "box2d.h"
class WorldManager
{
public:
	static WorldManager& Instance()
	{
		static WorldManager instance;
		return instance;
	}
	b2World* GetWorld();
	b2Body* CreateRigidBody(b2Vec2 position);
	b2Body* CreateDynamicRigidBody(b2Vec2 position);
	b2Body* CreateKinematicRigidBody(b2Vec2 position);
	b2Body* WorldManager::CreateBulletRigidBody(b2Vec2 position);
	void AddBody(b2Body* body) { bodies.push_back(body); }
private:
	WorldManager();
	~WorldManager();
	b2World* world;
	std::vector<b2Body*> bodies;
};
