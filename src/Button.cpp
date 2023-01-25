#include "Button.h"
#include <utility>
#include "Game.h"
#include "EventManager.h"
#include "TextureManager.h"
#include "WorldManager.h"


/**
 * @brief Construct a new Button:: Button object
 * 
 * @param image_path 
 * @param button_name 
 * @param type 
 * @param position 
 * @param is_centered 
 */
Button::Button(const std::string& image_path, std::string button_name, const GameObjectType type,
               const b2Vec2 position, const bool is_centered):
m_alpha(255), m_name(std::move(button_name)), m_isCentered(is_centered), m_active(true)
{
	TextureManager::Instance().Load(image_path,m_name);
	InitRigidBody();
	const auto size = TextureManager::Instance().GetTextureSize(m_name);
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));
	SetType(type);
}

Button::~Button()
= default;

void Button::Draw()
{
	// draw the button
	TextureManager::Instance().Draw(m_name, GetRigidBody()->GetPosition(), 0, m_alpha, m_isCentered);
}

void Button::Update()
{
	if(EventManager::Instance().IsMainWindowInFocus())
	{
		//check if mouse is over the Button
		OnMouseOver();

		// check if mouse outside the Button
		OnMouseOut();

		// check if left mouse is clicked
		OnLeftMouseButtonClick();
	}
	
}

void Button::Clean()
{
}

/**
 * @brief sets the alpha transparency of the button
 * @param alpha
 * @return void
 */
void Button::SetAlpha(const Uint8 alpha)
{
	m_alpha = alpha;
}

/**
 * @brief sets the button active boolean
 * @return void
 */
void Button::SetActive(const bool value)
{
	m_active = value;
}
void Button::InitRigidBody()
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(400.0f, 400.0f);
	bodyDef.enabled = true;
	bodyDef.type = b2_kinematicBody;
	m_rigidBody = WorldManager::Instance().GetWorld()->CreateBody(&bodyDef);
}
b2Body* Button::GetRigidBody()
{
	return m_rigidBody;
}