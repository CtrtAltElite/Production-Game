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
	veloDamp = {0.985, 0.985};
	SetType(GameObjectType::PLAYER);

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
			Camera::Instance().CameraDisplace(GetTransform()->position), 0.25f, GetTransform()->rotation.r*Util::Rad2Deg, 255, true);
		break;
	case PlayerAnimationState::PLAYER_IDLE_LEFT:
		TextureManager::Instance().PlayAnimation("sub_spritesheet", GetAnimation("idle"),
			Camera::Instance().CameraDisplace(GetTransform()->position), 0.25f, GetTransform()->rotation.r*Util::Rad2Deg, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case PlayerAnimationState::PLAYER_RUN_RIGHT:
		TextureManager::Instance().PlayAnimation("sub_spritesheet", GetAnimation("run"),
			Camera::Instance().CameraDisplace(GetTransform()->position), 0.75f, GetTransform()->rotation.r*Util::Rad2Deg, 255, true);
		break;
	case PlayerAnimationState::PLAYER_RUN_LEFT:
		TextureManager::Instance().PlayAnimation("sub_spritesheet", GetAnimation("run"),
			Camera::Instance().CameraDisplace(GetTransform()->position), 0.75f, GetTransform()->rotation.r*Util::Rad2Deg, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	default:
		break;
	}
}

void Player::Update()
{
	m_mousePos = Util::GetMousePos();
	LookAtMouse();
	Move();
	GetRigidBody()->velocity*=veloDamp;
	Camera::Instance().GetTransform()->position=GetTransform()->position-glm::vec2{1280/2,720/2};
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
	GetRigidBody()->velocity-=Util::Normalize(glm::vec2{GetTransform()->position.x-m_mousePos.x,GetTransform()->position.y-m_mousePos.y})*m_speed;
}
void Player::LookAtMouse()
{
	float angleToMouse = atan2(m_mousePos.y-GetTransform()->position.y,m_mousePos.x-GetTransform()->position.x);
	GetTransform()->rotation.r = angleToMouse;
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
