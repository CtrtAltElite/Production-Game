#pragma once
#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__
#include <string>
#include "box2d.h"

// enums
#include "GameObjectType.h"


class GameObject {
public:
	GameObject();
	virtual ~GameObject();

	// Draw the object
	virtual void Draw() = 0;

	// Update the object
	virtual void Update() = 0;

	// remove anything that needs to be deleted
	virtual void Clean() = 0;

	// getters for common variables

	// getters and setters for physics properties
	

	// getters and setters for game object properties
	[[nodiscard]] int GetWidth() const;
	[[nodiscard]] int GetHeight() const;
	void SetWidth(int new_width);
	void SetHeight(int new_height);
	[[nodiscard]] GameObjectType GetType() const;
	void SetType(GameObjectType new_type);

	void SetEnabled(bool state);
	[[nodiscard]] bool IsEnabled() const;

	void SetVisible(bool state);
	[[nodiscard]] bool IsVisible() const;

	bool isColliding = false;
	b2Body* GetRigidBody();

private:
	// rigid body component
	


	// size variables
	int m_width;
	int m_height;
	GameObjectType m_type;
	b2Body* m_rigidBody;
	bool m_enabled;
	bool m_visible;
};

#endif /* defined (__GAME_OBJECT__) */