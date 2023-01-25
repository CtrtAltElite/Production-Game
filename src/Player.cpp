#include "Player.h"

#include <Windows.h>

#include "Camera.h"
#include "Game.h"
#include "TextureManager.h"
#include "Util.h"
#include "WorldManager.h"

Player::Player()
{
	TextureManager::Instance().Load("../Assets/textures/ncl.png", "player");
	InitRigidBody();
	// set frame width
	SetWidth(53);
	// set frame height
	SetHeight(58);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(GetWidth()/3, GetHeight()/3);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.5f;
	GetRigidBody()->CreateFixture(&fixtureDef);
	isColliding = false;
	SetType(GameObjectType::PLAYER);

}

Player::~Player()
= default;
void Player::InitRigidBody()
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(500.0f, 500.0f);
	bodyDef.angle = 0;
	bodyDef.type = b2_dynamicBody;
	bodyDef.linearDamping = 0.6f;
	bodyDef.angularDamping = 0.8f;
	bodyDef.enabled = true;
	m_rigidBody = WorldManager::Instance().GetWorld()->CreateBody(&bodyDef);
}

void Player::Draw()
{
	// alias for x and y
	float x = m_rigidBody->GetPosition().x;
	float y = m_rigidBody->GetPosition().y;
	// draw the player according to animation state
	TextureManager::Instance().Draw("player", {x,y}, GetRigidBody()->GetAngle()*Util::Rad2Deg, 255, true);
}

void Player::Update()
{
	m_mousePos = Game::Instance().GetMousePosition();
	b2Vec2 toTarget = { m_mousePos.x - GetRigidBody()->GetPosition().x, m_mousePos.y - GetRigidBody()->GetPosition().y };
	m_angleToMouse = b2Atan2(toTarget.y, toTarget.x);
	RotateToMouse();
}

void Player::Clean()
{
}
void Player::MoveAtMouse()
{
	
	b2Vec2 vector = { cos(GetRigidBody()->GetAngle()),sin(GetRigidBody()->GetAngle()) };
	GetRigidBody()->ApplyForceToCenter({ vector.x * 1000000.0f,vector.y * 1000000.0f }, true);



	//std::cout << "Body Angle: " << GetRigidBody()->GetAngle() * Util::Rad2Deg << std::endl;
	//std::cout << "Angle to mouse: " << m_angleToMouse * Util::Rad2Deg << std::endl;
	//std::cout << "Angular Velo: " << GetRigidBody()->GetAngularVelocity() << std::endl;
	//std::cout << "Inertia: " << GetRigidBody()->GetInertia() << std::endl;
	//std::cout << "X: "<<GetRigidBody()->GetPosition().x << " Y: " << GetRigidBody()->GetPosition().y << std::endl;
	//std::cout << "MOUSE POS X:" << m_mousePos.x << ", Y: " << m_mousePos.y << std::endl;
	//std::cout << "Linear Velocity X: " << GetRigidBody()->GetLinearVelocity().x <<", Y: "<< GetRigidBody()->GetLinearVelocity().y<< std::endl;
	
}
void Player::RotateToMouse()
{
	float nextAngle = GetRigidBody()->GetAngle() + GetRigidBody()->GetAngularVelocity() / 60.0;
	float totalRotation = m_angleToMouse - nextAngle;
	while (totalRotation < -180 * Util::Deg2Rad) totalRotation += 360 * Util::Deg2Rad;
	while (totalRotation > 180 * Util::Deg2Rad) totalRotation -= 360 * Util::Deg2Rad;
	float desiredAngularVelocity = totalRotation * 60;
	float change = 1 * Util::Deg2Rad; //allow 1 degree rotation per time step
	desiredAngularVelocity = std::min(change, std::max(-change, desiredAngularVelocity));
	float impulse = GetRigidBody()->GetInertia() * desiredAngularVelocity;
	GetRigidBody()->ApplyAngularImpulse(impulse*10.0f,true);
	
	
}

b2Body* Player::GetRigidBody()
{
	return m_rigidBody;
}