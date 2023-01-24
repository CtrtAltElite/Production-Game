#pragma once
#ifndef __BUTTON__
#define __BUTTON__

#include "DisplayObject.h"
#include <SDL.h>
#include <glm/detail/type_vec.hpp>

#include "UIControl.h"

class Button : public UIControl
{
public:
	explicit Button(const std::string& image_path = "../Assets/textures/StartButton.png", 
	                std::string button_name = "startButton", 
	                GameObjectType type = GameObjectType::START_BUTTON, 
					b2Vec2 position = b2Vec2{ 0.0f, 0.0f }, bool is_centered = true);
	
	~Button() override;

	// Life Cycle Events
	void Draw() override;
	void Update() override;
	void Clean() override;
	void InitRigidBody() override;
	b2Body* GetRigidBody() override;

	// button setters
	void SetAlpha(Uint8 alpha);
	void SetActive(bool value);
	
private:
	Uint8 m_alpha;
	std::string m_name;
	bool m_isCentered;
	bool m_active;
	b2Body* m_rigidBody;
};

#endif /* defined (__BUTTON__) */