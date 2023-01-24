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
	InitRigidBody();
	// set frame width
	SetWidth(53);

	// set frame height
	SetHeight(58);
	
	m_speed = 0.4f;
	m_maxvelo = 7.0f;
	m_velodecay = 0.1f;
	isColliding = true;
	SetType(GameObjectType::PLAYER);

	BuildAnimations();
}

Player::~Player()
= default;
void Player::InitRigidBody()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(50.0f, 50.0f);
	bodyDef.enabled = true;
	m_rigidBody = Game::Instance().world->CreateBody(&bodyDef);
}

void Player::Draw()
{
	// alias for x and y
	const auto x = static_cast<int>(m_rigidBody->GetPosition().x-Game::Instance().camera.x);
	const auto y = static_cast<int>(m_rigidBody->GetPosition().y-Game::Instance().camera.y);
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
	/*
	b2Vec2 temp = m_rigidBody->GetLinearVelocity();
	if (abs(temp.x > 0))
	{
		if (abs(temp.x) - m_velodecay < 0.0f)
		{
			temp.x = 0;
		}
		else
		{
			if (m_rigidBody->GetLinearVelocity().x > 0)
			{
				temp.x -= m_velodecay;
			}
			else
			{
				temp.x += m_velodecay;
			}
		}
	}
	if (abs(temp.y) > 0)
	{
		if (abs(temp.y) - m_velodecay < 0)
		{
			temp.y = 0;
		}
		else
		{
			if (temp.y > 0)
			{
				temp.y -= m_velodecay;
			}
			else
			{
				temp.y += m_velodecay;
			}
		}
	}
	m_rigidBody->SetLinearVelocity(temp);
	if (temp.x > m_maxvelo)
	{
		temp.x = m_maxvelo;
	}
	if (temp.x < -m_maxvelo)
	{
		temp.x = -m_maxvelo;
	}
	if (temp.y > m_maxvelo)
	{
		temp.y = m_maxvelo;
	}
	if (temp.y < -m_maxvelo)
	{
		temp.y = -m_maxvelo;
	}
	//std::cout << "X VELOCITY: " << GetRigidBody()->velocity.x << std::endl << " Y VELOCITY: " << GetRigidBody()->velocity.y << std::endl;
	GetRigidBody()->SetTransform(GetRigidBody()->GetPosition()+temp, 0);
	*/

	//USE BOX 2D PHYSICS INSTEAD
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
