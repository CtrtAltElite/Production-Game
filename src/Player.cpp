#include "Player.h"

#include <Windows.h>

#include "Camera.h"
#include "Game.h"
#include "TextureManager.h"
#include "Util.h"
#include "WorldManager.h"

// Constructor, initializes a lot of stuff like RigidBody and any physics or texture variables.
Player::Player()
{
	TextureManager::Instance().Load("../Assets/textures/ncl.png", "player");
	InitRigidBody();
	SetWidth(53); // Setting width of frame
	SetHeight(58); // Setting height of frame
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

// Just a default destructor
Player::~Player()
= default;


void Player::InitRigidBody()
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(500.0f, 500.0f);
	bodyDef.angle = 0;
	bodyDef.type = b2_dynamicBody;
	bodyDef.linearDamping = 0.8f;
	bodyDef.angularDamping = 1.0f;
	bodyDef.enabled = true;
	m_rigidBody = WorldManager::Instance().GetWorld()->CreateBody(&bodyDef);
}

void Player::Draw()
{
	//add fixture and rigid body render
	TextureManager::Instance().Draw("player", Camera::Instance().CameraDisplace(m_rigidBody->GetPosition()), GetRigidBody()->GetAngle() * Util::Rad2Deg, 255, true);
	/*for (b2Fixture* f = GetRigidBody()->GetFixtureList(); f; f = f->GetNext())
	{
		b2Shape::Type shapeType = f->GetType();
		if (shapeType == b2Shape::e_polygon)
		{
			b2PolygonShape* polygon = (b2PolygonShape*)f->GetShape();
			SDL_RenderDrawLinesF(Renderer::Instance().GetRenderer(), polygon->m_vertices, 4);
		}
	}*/
	
}

void Player::Update()
{
	//Camera displace and mouse position cause a ton of problems. remove comment in Camera.cpp to disable camera
	m_mousePos = Camera::Instance().CameraDisplace(Game::Instance().GetMousePosition());
	b2Vec2 displacedPos = Camera::Instance().CameraDisplace(GetRigidBody()->GetPosition());
	b2Vec2 toTarget = { m_mousePos.x - displacedPos.x, m_mousePos.y - displacedPos.y };
	m_angleToMouse = b2Atan2(toTarget.y, toTarget.x);
	RotateToMouse();
}

void Player::Clean()
{
}

void Player::MoveAtMouse()
{
	
	b2Vec2 vector = { cos(GetRigidBody()->GetAngle()),sin(GetRigidBody()->GetAngle()) };
	
	if (GetRigidBody()->GetTransform().p != vector)
	{
		GetRigidBody()->ApplyForceToCenter({ vector.x * m_speed,vector.y * m_speed }, true);
	}


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
	float nextAngle = GetRigidBody()->GetAngle() + GetRigidBody()->GetAngularVelocity() / 10.0;
	float totalRotation = m_angleToMouse - nextAngle;

	while (totalRotation < -180 * Util::Deg2Rad) totalRotation += 360 * Util::Deg2Rad;
	while (totalRotation > 180 * Util::Deg2Rad) totalRotation -= 360 * Util::Deg2Rad;
	float desiredAngularVelocity = totalRotation * 10;
	float change = 1 * Util::Deg2Rad; //allow 1 degree rotation per time step
	desiredAngularVelocity = std::min(change, std::max(-change, desiredAngularVelocity));
	float impulse = GetRigidBody()->GetInertia() * desiredAngularVelocity;
	GetRigidBody()->ApplyAngularImpulse(impulse*100.0f,true);

}

b2Body* Player::GetRigidBody()
{
	return m_rigidBody;
}