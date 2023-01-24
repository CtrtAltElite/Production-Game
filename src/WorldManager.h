#pragma once
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
	b2Body* CreateRigidBody(b2Vec2 position) const;
	b2Body* CreateDynamicRigidBody(b2Vec2 position) const;
	b2Body* CreateKinematicRigidBody(b2Vec2 position) const;
private:
	WorldManager();
	~WorldManager();
	b2World* world;
};
