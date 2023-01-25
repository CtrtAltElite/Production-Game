#include "Player.h"

#include "Camera.h"
#include "Game.h"
#include "TextureManager.h"
#include "WorldManager.h"

Player::Player()
{
	TextureManager::Instance().Load("../Assets/textures/Circle.png", "player");
	InitRigidBody();
	// set frame width
	SetWidth(53);
	// set frame height
	SetHeight(58);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(GetWidth()/3, GetHeight()/3);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 0.5f;
	fixtureDef.friction = 0.5f;
	GetRigidBody()->CreateFixture(&fixtureDef);
	isColliding = false;
	SetType(GameObjectType::PLAYER);

}

Player::~Player()
= default;
void Player::InitRigidBody()
{
	m_rigidBody = WorldManager::Instance().CreateDynamicRigidBody({ 500.0f,500.0f });
}

void Player::Draw()
{
	// alias for x and y
	const auto x = static_cast<int>(m_rigidBody->GetPosition().x- Camera::Instance().GetPosition().x);
	const auto y = static_cast<int>(m_rigidBody->GetPosition().y-Camera::Instance().GetPosition().y);
	// draw the player according to animation state
	TextureManager::Instance().Draw("player", m_rigidBody->GetPosition(), 0, 255, true);
}

void Player::Update()
{
	
}

void Player::Clean()
{
}
void Player::MoveAtMouse()
{
	glm::ivec2 mousepos = Game::Instance().GetMousePosition();
	float angle = atan2((GetRigidBody()->GetPosition().y - mousepos.y) - Camera::Instance().GetPosition().y, (GetRigidBody()->GetPosition().x - mousepos.x) - Camera::Instance().GetPosition().x);
	b2Vec2 vector = { -cos(angle)*100000.0f,-sin(angle)*100000.0f };
	GetRigidBody()->ApplyForceToCenter(vector, true);
	std::cout << "X: "<<GetRigidBody()->GetPosition().x << " Y: " << GetRigidBody()->GetPosition().y << std::endl;
	std::cout << "MOUSE POS X:" << mousepos.x << ", Y: " << mousepos.y << std::endl;
	std::cout << "Linear Velocity X: " << GetRigidBody()->GetLinearVelocity().x <<", Y: "<< GetRigidBody()->GetLinearVelocity().y<< std::endl;
}


b2Body* Player::GetRigidBody()
{
	return m_rigidBody;
}