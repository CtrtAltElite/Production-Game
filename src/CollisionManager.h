#pragma once
#ifndef __COLLISION_MANAGER__
#define __COLLISION_MANAGER__

// core libraries
#include <iostream>

#include "GameObject.h"
#include <glm/gtx/norm.hpp>

#include "Agent.h"
#include "SoundManager.h"

class CollisionManager
{
public:
	static int SquaredDistance(b2Vec2 p1, b2Vec2 p2);
	static bool SquaredRadiusCheck(GameObject* object1, GameObject* object2);

	static bool AABBCheck(GameObject* object1, GameObject* object2);

	static bool LineLineCheck(b2Vec2 line1_start, b2Vec2 line1_end, b2Vec2 line2_start, b2Vec2 line2_end);

	static bool LineRectCheck(b2Vec2 line_start, b2Vec2 line_end, b2Vec2 rect_start, float rect_width, float rect_height);
	static bool LineRectEdgeCheck(b2Vec2 line_start, b2Vec2 rect_start, float rect_width, float rect_height);


	static int MinSquaredDistanceLineLine(b2Vec2 line1_start, b2Vec2 line1_end, b2Vec2 line2_start, b2Vec2 line2_end);
	//static bool LineAABBCheck(Ship* object1, GameObject* object2);

	static int CircleAABBSquaredDistance(b2Vec2 circle_centre, int circle_radius, b2Vec2 box_start, int box_width, int box_height);
	static bool CircleAABBCheck(GameObject* object1, GameObject* object2);

	static bool PointRectCheck(b2Vec2 point, b2Vec2 rect_start, float rect_width, float rect_height);

	static bool LOSCheck(Agent* agent, b2Vec2 end_point, const std::vector<DisplayObject*>& objects, DisplayObject* target);

private:
	CollisionManager();
	~CollisionManager();
};

#endif /* defined (__COLLISION_MANAGER__) */