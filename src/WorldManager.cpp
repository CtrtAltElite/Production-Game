#include "WorldManager.h"

#include "Game.h"

WorldManager::WorldManager()
{
	b2Vec2 gravity = b2Vec2(0.0f, 0.0f);
	WorldManager::world = new b2World(gravity);
}
WorldManager::~WorldManager()
{
	
}
b2World* WorldManager::GetWorld()
{
	return world;
}
b2Body* WorldManager::CreateRigidBody(b2Vec2 position)
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(position.x, position.y);
	b2Body* rigidBody = world->CreateBody(&bodyDef);
	bodyDef.enabled = true;
	bodies.push_back(rigidBody);
	return rigidBody;
}
b2Body* WorldManager::CreateDynamicRigidBody(b2Vec2 position)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.enabled = true;
	b2Body* rigidBody = world->CreateBody(&bodyDef);
	bodies.push_back(rigidBody);
	return rigidBody;
}
b2Body* WorldManager::CreateKinematicRigidBody(b2Vec2 position)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.enabled = true;
	b2Body* rigidBody = world->CreateBody(&bodyDef);
	bodies.push_back(rigidBody);
	return rigidBody;
}
b2Body* WorldManager::CreateBulletRigidBody(b2Vec2 position)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.enabled = true;
	bodyDef.bullet = true;
	b2Body* rigidBody = world->CreateBody(&bodyDef);
	bodies.push_back(rigidBody);
	return rigidBody;
}
