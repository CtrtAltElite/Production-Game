#pragma once
#ifndef __OBSTACLE__
#define __OBSTACLE__
#include "DisplayObject.h"

class Obstacle : virtual public DisplayObject
{
public:
	// constructors
	Obstacle();
	Obstacle(const char* fileName, const char* texture);
	Obstacle(const char* fileName, const char* texture, const char* txtName);

	// destructor
	~Obstacle() override;
	
	// life cycle functions
	void Draw() override;
	void Update() override;
	void Clean() override;
	void UpdatePlacement();

	// Misc functions
	[[nodiscard]] bool GetDeleteMe() const;
	void SetDeleteMe(bool deleteMe);
	bool m_isPlacing = false;
	std::string textureName;
	std::string tag;

private:
	bool m_deleteMe;
	bool m_isSpriteSheet;
};

class ObstaclePool : public DisplayObject
{
public:
	ObstaclePool();

	// Lifecycle functions
	void Update() override;
	void Clean();
	void Draw() override;

	// Specific functions
	std::vector<Obstacle*> GetPool();
	void Spawn(Obstacle* obstacleType);

private:
	std::vector<Obstacle*> m_obstacles;
};


#endif /* defined (__OBSTACLE__) */