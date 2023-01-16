#include "Player.h"

#include "Game.h"
#include "TextureManager.h"

Player::Player(): m_currentAnimationState(PlayerAnimationState::PLAYER_IDLE_RIGHT)
{
	TextureManager::Instance().LoadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png", 
		"spritesheet");

	SetSpriteSheet(TextureManager::Instance().GetSpriteSheet("spritesheet"));
	
	// set frame width
	SetWidth(53);

	// set frame height
	SetHeight(58);

	m_speed = 1.0f;
	m_maxvelo = 10.0f;
	m_velodecay = 0.8f;
	GetTransform()->position = glm::vec2(400.0f, 300.0f);
	GetRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->isColliding = false;
	SetType(GameObjectType::PLAYER);

	BuildAnimations();
}

Player::~Player()
= default;

void Player::Draw()
{
	// alias for x and y
	const auto x = static_cast<int>(GetTransform()->position.x-Game::Instance().camera.x);
	const auto y = static_cast<int>(GetTransform()->position.y-Game::Instance().camera.y);

	// draw the player according to animation state
	switch(m_currentAnimationState)
	{
	case PlayerAnimationState::PLAYER_IDLE_RIGHT:
		TextureManager::Instance().PlayAnimation("spritesheet", GetAnimation("idle"),
			x, y, 0.12f, 0, 255, true);
		break;
	case PlayerAnimationState::PLAYER_IDLE_LEFT:
		TextureManager::Instance().PlayAnimation("spritesheet", GetAnimation("idle"),
			x, y, 0.12f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case PlayerAnimationState::PLAYER_RUN_RIGHT:
		TextureManager::Instance().PlayAnimation("spritesheet", GetAnimation("run"),
			x, y, 0.25f, 0, 255, true);
		break;
	case PlayerAnimationState::PLAYER_RUN_LEFT:
		TextureManager::Instance().PlayAnimation("spritesheet", GetAnimation("run"),
			x, y, 0.25f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	default:
		break;
	}
	
}

void Player::Update()
{
	
	if (abs(GetRigidBody()->velocity.x) > 0)
	{
		if (abs(GetRigidBody()->velocity.x) - m_velodecay < 0)
		{
			GetRigidBody()->velocity.x = 0;
		}
		else
		{
			if (GetRigidBody()->velocity.x > 0)
			{
				GetRigidBody()->velocity.x -= m_velodecay;
			}
			else
			{
				GetRigidBody()->velocity.x += m_velodecay;
			}
		}
			
	}
	if (abs(GetRigidBody()->velocity.y) > 0)
	{
		if (abs(GetRigidBody()->velocity.y) - m_velodecay < 0)
		{
			GetRigidBody()->velocity.y = 0;
		}
		else
		{
			if (GetRigidBody()->velocity.y > 0)
			{
				GetRigidBody()->velocity.y -= m_velodecay;
			}
			else
			{
				GetRigidBody()->velocity.y += m_velodecay;
			}
		}

	}
	if (GetRigidBody()->velocity.x > m_maxvelo)
	{
		GetRigidBody()->velocity.x = m_maxvelo;
	}
	if (GetRigidBody()->velocity.x < -m_maxvelo)
	{
		GetRigidBody()->velocity.x = -m_maxvelo;
	}
	if (GetRigidBody()->velocity.y > m_maxvelo)
	{
		GetRigidBody()->velocity.y = m_maxvelo;
	}
	if (GetRigidBody()->velocity.y < -m_maxvelo)
	{
		GetRigidBody()->velocity.y = -m_maxvelo;
	}
	
	GetTransform()->position += GetRigidBody()->velocity * m_speed;
}

void Player::Clean()
{
}

void Player::SetAnimationState(const PlayerAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

void Player::BuildAnimations()
{
	auto idle_animation = Animation();

	idle_animation.name = "idle";
	idle_animation.frames.push_back(GetSpriteSheet()->GetFrame("megaman-idle-0"));
	idle_animation.frames.push_back(GetSpriteSheet()->GetFrame("megaman-idle-1"));
	idle_animation.frames.push_back(GetSpriteSheet()->GetFrame("megaman-idle-2"));
	idle_animation.frames.push_back(GetSpriteSheet()->GetFrame("megaman-idle-3"));

	SetAnimation(idle_animation);

	auto run_animation = Animation();

	run_animation.name = "run";
	run_animation.frames.push_back(GetSpriteSheet()->GetFrame("megaman-run-0"));
	run_animation.frames.push_back(GetSpriteSheet()->GetFrame("megaman-run-1"));
	run_animation.frames.push_back(GetSpriteSheet()->GetFrame("megaman-run-2"));
	run_animation.frames.push_back(GetSpriteSheet()->GetFrame("megaman-run-3"));

	SetAnimation(run_animation);
}
