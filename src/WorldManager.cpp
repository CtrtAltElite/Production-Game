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

