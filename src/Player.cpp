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
	SetWidth(58);
	SetHeight(30);
	m_speed = 5.0f;
	m_maxSpeed = 200.0f;
	GetTransform()->position = glm::vec2(400.0f, 300.0f);
	GetRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->bounds=glm::vec2(GetWidth(), GetHeight());
	GetRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->isColliding = false;
	GetRigidBody()->velocityDampening = {0.985, 0.985};
	GetRigidBody()->angularVelocityDampening = 0.96f;
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
	Util::DrawRect(Camera::Instance().CameraDisplace(this) -
			glm::vec2(this->GetWidth() * 0.5f, this->GetHeight() * 0.5f),
			this->GetWidth(), this->GetHeight());
	//SDL_RenderDrawRectF(Renderer::Instance().GetRenderer(),new SDL_FRect{Camera::Instance().CameraDisplace(this).x,Camera::Instance().CameraDisplace(this).y,static_cast<float>(GetWidth()),static_cast<float>(GetHeight())});
	switch(m_currentAnimationState)
	{
	case PlayerAnimationState::PLAYER_IDLE_RIGHT:
		TextureManager::Instance().PlayAnimation("sub_spritesheet", GetAnimation("idle"),
			Camera::Instance().CameraDisplace(this), animVelo, GetTransform()->rotation.r*Util::Rad2Deg, 255, true);
		break;
	case PlayerAnimationState::PLAYER_IDLE_LEFT:
		TextureManager::Instance().PlayAnimation("sub_spritesheet", GetAnimation("idle"),
			Camera::Instance().CameraDisplace(this), animVelo, GetTransform()->rotation.r*Util::Rad2Deg, 255, true, SDL_FLIP_VERTICAL);
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
	Camera::Instance().GetTransform()->position.x = Util::Clamp(Camera::Instance().GetTransform()->position.x,-Config::LEVEL_BOUNDARIES_X,Config::LEVEL_BOUNDARIES_X);
	Camera::Instance().GetTransform()->position.y = Util::Clamp(Camera::Instance().GetTransform()->position.y,-Config::LEVEL_BOUNDARIES_Y,Config::LEVEL_BOUNDARIES_Y);
	CollisionManager::RotateAABB(this, this->GetTransform()->rotation.r*Util::Rad2Deg);
}
void Player::Clean()
{
}
void Player::SetAnimationState(const PlayerAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

void Player::SetMaxSpeed(float maxSpeed)
{
	m_maxSpeed = maxSpeed;
}

void Player::SetFlipped(bool flipped)
{
	m_flipped = flipped;
}

void Player::SetScore(float score)
{
	m_score = score;
}

void Player::SetKillcount(int killcount)
{
	m_killCount = killcount;
}

void Player::SetHealth(float health)
{
	m_Health = health;
}

void Player::SetIsDead(bool isDead)
{
	isDead = m_isDead;
}

void Player::MoveAtMouse()
{
	GetRigidBody()->velocity+=glm::vec2{cos(GetTransform()->rotation.r),sin(GetTransform()->rotation.r)}*m_speed;
	animVelo+=0.12f;
}
void Player::LookAtMouse()
{
	float angleToMouse = atan2(m_mousePos.y-Camera::Instance().CameraDisplace(this).y,m_mousePos.x-Camera::Instance().CameraDisplace(this).x);
	float nextAngle = GetTransform()->rotation.r + GetRigidBody()->angularVelocity/10;
	float totalRotation = angleToMouse - nextAngle;
	while (totalRotation < -180 * Util::Deg2Rad) totalRotation += 360 * Util::Deg2Rad;
	while (totalRotation > 180 * Util::Deg2Rad) totalRotation -= 360 * Util::Deg2Rad;
	float desiredAngularVelocity = totalRotation*10;
	float change = 1000 * Util::Deg2Rad;
	desiredAngularVelocity = std::min(change, std::max(-change, desiredAngularVelocity));
	GetRigidBody()->angularVelocity+=desiredAngularVelocity/10;
	
}

float Player::GetMaxSpeed() const
{
	return m_maxSpeed;
}

bool Player::GetFlipped() const
{
	return m_flipped;
}

float Player::GetScore()
{
	return m_score;
}

int Player::GetKillcount()
{
	return m_killCount;
}

float Player::GetHealth()
{
	return m_Health;
}

bool Player::GetIsDead()
{
	return m_isDead;
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
