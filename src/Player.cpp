#include "Player.h"

#include "Camera.h"
#include "TextureManager.h"
#include "Util.h"
#include "Game.h"

Player::Player(): m_currentAnimationState(PlayerAnimationState::PLAYER_IDLE_RIGHT)
{
	TextureManager::Instance().LoadSpriteSheet(
		"../Assets/sprites/sub_sprite.txt",
		"../Assets/sprites/sub_sprite.png", 
		"sub_spritesheet");

	SetSpriteSheet(TextureManager::Instance().GetSpriteSheet("sub_spritesheet"));
	
	// set frame width
	SetWidth(53);

	// set frame height
	SetHeight(58);

	m_speed = 5.0f;
	m_maxSpeed = 200.0f;
	GetTransform()->position = glm::vec2(400.0f, 300.0f);
	GetRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->isColliding = false;
	GetRigidBody()->velocityDampening = {0.985, 0.985};
	GetRigidBody()->angularVelocityDampening = 0.95f;
	SetType(GameObjectType::PLAYER);
	animVelo = 0.33f;
	animVeloDamp = 0.99f;

	BuildAnimations();
}

Player::~Player()
= default;

void Player::Draw()
{
	
	// draw the player according to animation state
	switch(m_currentAnimationState)
	{
	case PlayerAnimationState::PLAYER_IDLE_RIGHT:
		TextureManager::Instance().PlayAnimation("sub_spritesheet", GetAnimation("idle"),
			Camera::Instance().CameraDisplace(GetTransform()->position), animVelo, GetTransform()->rotation.r*Util::Rad2Deg, 255, true);
		break;
	case PlayerAnimationState::PLAYER_IDLE_LEFT:
		TextureManager::Instance().PlayAnimation("sub_spritesheet", GetAnimation("idle"),
			Camera::Instance().CameraDisplace(GetTransform()->position), animVelo, GetTransform()->rotation.r*Util::Rad2Deg, 255, true, SDL_FLIP_VERTICAL);
		break;
	default:
		break;
	}
}

void Player::Update()
{
	while (GetTransform()->rotation.r < 0 * Util::Deg2Rad) GetTransform()->rotation.r += 360 * Util::Deg2Rad;
	while (GetTransform()->rotation.r > 360 * Util::Deg2Rad) GetTransform()->rotation.r -= 360 * Util::Deg2Rad;
	if (GetTransform()->rotation.r*Util::Rad2Deg > 90 && GetTransform()->rotation.r*Util::Rad2Deg < 270)
	{
		SetAnimationState(PlayerAnimationState::PLAYER_IDLE_LEFT);
		SetFlipped(true);
	}
	else
	{
		SetAnimationState(PlayerAnimationState::PLAYER_IDLE_RIGHT);
		SetFlipped(false);
	}
	animVelo*=animVeloDamp;
	animVelo = Util::Clamp(animVelo,0.33f,1.5f);
	m_mousePos = Util::GetMousePos();
	LookAtMouse();
	Move();
	//std::cout << GetTransform()->rotation.r*Util::Rad2Deg << std::endl;
	//std::cout << animVelo << std::endl;
}
void Player::Move()
{
	const float dt =Game::Instance().GetDeltaTime();
	const glm::vec2 initial_position = GetTransform()->position;
	const glm::vec2 velocity_term = GetRigidBody()->velocity * dt;
	const glm::vec2 acceleration_term = GetRigidBody()->acceleration * 0.5f;
	const glm::vec2 final_position = initial_position + velocity_term + acceleration_term;
	GetTransform()->position = final_position;
	GetRigidBody()->velocity += GetRigidBody()->acceleration;
	GetRigidBody()->velocity = Util::Clamp(GetRigidBody()->velocity,GetMaxSpeed());
	const float initial_rotation = GetTransform()->rotation.r;
	const float angularVelocity_term = GetRigidBody()->angularVelocity * dt;
	const float angularAcceleration_term = GetRigidBody()->angularAcceleration * 0.5f;
	const float final_rotation = initial_rotation + angularVelocity_term + angularAcceleration_term;
	GetTransform()->rotation.r = final_rotation;
	GetRigidBody()->angularVelocity += GetRigidBody()->angularAcceleration;
	GetRigidBody()->velocity*=GetRigidBody()->velocityDampening;
	GetRigidBody()->angularVelocity*=GetRigidBody()->angularVelocityDampening;
	Camera::Instance().GetTransform()->position.x = GetTransform()->position.x - static_cast<float>(Config::SCREEN_WIDTH)/2;
	Camera::Instance().GetTransform()->position.y = GetTransform()->position.y - static_cast<float>(Config::SCREEN_HEIGHT)/2;
}
void Player::Clean()
{
}
void Player::SetAnimationState(const PlayerAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

void Player::MoveAtMouse()
{
	GetRigidBody()->velocity+=glm::vec2{cos(GetTransform()->rotation.r),sin(GetTransform()->rotation.r)}*m_speed;
	animVelo+=0.1f;
}
void Player::LookAtMouse()
{
	float angleToMouse = atan2(m_mousePos.y-Camera::Instance().CameraDisplace(GetTransform()->position).y,m_mousePos.x-Camera::Instance().CameraDisplace(GetTransform()->position).x);
	float nextAngle = GetTransform()->rotation.r + GetRigidBody()->angularVelocity / 10.0f;
	float totalRotation = angleToMouse - nextAngle;
	while (totalRotation < -180 * Util::Deg2Rad) totalRotation += 360 * Util::Deg2Rad;
	while (totalRotation > 180 * Util::Deg2Rad) totalRotation -= 360 * Util::Deg2Rad;
	float desiredAngularVelocity = totalRotation * 10.0f;
	float change = 1000 * Util::Deg2Rad; //allow 10 degree rotation per time step
	desiredAngularVelocity = std::min(change, std::max(-change, desiredAngularVelocity));
	GetRigidBody()->angularVelocity+=desiredAngularVelocity/10;
	
}

void Player::BuildAnimations()
{
	auto idle_animation = Animation();

	idle_animation.name = "idle";
	idle_animation.frames.push_back(GetSpriteSheet()->GetFrame("sub1"));
	idle_animation.frames.push_back(GetSpriteSheet()->GetFrame("sub2"));
	idle_animation.frames.push_back(GetSpriteSheet()->GetFrame("sub3"));
	idle_animation.frames.push_back(GetSpriteSheet()->GetFrame("sub4"));
	idle_animation.frames.push_back(GetSpriteSheet()->GetFrame("sub5"));
	idle_animation.frames.push_back(GetSpriteSheet()->GetFrame("sub6"));
	idle_animation.frames.push_back(GetSpriteSheet()->GetFrame("sub7"));
	idle_animation.frames.push_back(GetSpriteSheet()->GetFrame("sub8"));

	SetAnimation(idle_animation);

	auto run_animation = Animation();

	run_animation.name = "run";
	run_animation.frames.push_back(GetSpriteSheet()->GetFrame("sub1"));
	run_animation.frames.push_back(GetSpriteSheet()->GetFrame("sub2"));
	run_animation.frames.push_back(GetSpriteSheet()->GetFrame("sub3"));
	run_animation.frames.push_back(GetSpriteSheet()->GetFrame("sub4"));
	run_animation.frames.push_back(GetSpriteSheet()->GetFrame("sub5"));
	run_animation.frames.push_back(GetSpriteSheet()->GetFrame("sub6"));
	run_animation.frames.push_back(GetSpriteSheet()->GetFrame("sub7"));
	run_animation.frames.push_back(GetSpriteSheet()->GetFrame("sub8"));

	SetAnimation(run_animation);
}
