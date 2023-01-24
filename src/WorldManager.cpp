#include "WorldManager.h"

#include "Game.h"

WorldManager::WorldManager()
{
	b2Vec2 gravity = b2Vec2(0.0f, 9.81f);
	WorldManager::world = new b2World(gravity);
}
WorldManager::~WorldManager()
{
	
}
b2World* WorldManager::GetWorld()
{
	return world;
}
b2Body* WorldManager::CreateRigidBody(b2Vec2 position) const
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(position.x, position.y);
	b2Body* rigidBody = world->CreateBody(&bodyDef);
	return rigidBody;
}
b2Body* WorldManager::CreateDynamicRigidBody(b2Vec2 position) const
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	b2Body* rigidBody = world->CreateBody(&bodyDef);
	return rigidBody;
}
b2Body* WorldManager::CreateKinematicRigidBody(b2Vec2 position) const
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(position.x, position.y);
	b2Body* rigidBody = world->CreateBody(&bodyDef);
	return rigidBody;
}