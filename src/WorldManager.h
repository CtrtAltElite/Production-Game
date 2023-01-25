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
private:
	WorldManager();
	~WorldManager();
	b2World* world;
};
