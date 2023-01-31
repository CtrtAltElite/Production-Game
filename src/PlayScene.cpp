#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "Camera.h"
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"
#include "WorldManager.h"


// NOTE: "The World" refers to the scene, where all of the physics and movement functions take place


// Constructor, setting the size of the screen and starting off the scene
PlayScene::PlayScene():m_ScreenHeight(720), m_ScreenWidth(1280)
{
	PlayScene::Start();
}

// Basic destructor
PlayScene::~PlayScene()
= default;


// Lets start off this scene!
void PlayScene::Start()
{
	InitRigidBody();
	// Player Sprite
	m_pBackground = new Background();
	AddChild(m_pBackground);
	m_pPlayer = new Player();
	AddChild(m_pPlayer);
	m_pShark = new Shark();
	AddChild(m_pShark);

}

// Initializing the Rigidbody, setting some base values and then adding it to the World
void PlayScene::InitRigidBody()
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(0.0f, 0.0f);
	bodyDef.enabled = true;
	bodyDef.type = b2_dynamicBody;
	m_rigidBody = WorldManager::Instance().GetWorld()->CreateBody(&bodyDef);
}

// Think of this as ::Render() basically, happens all the time
void PlayScene::Draw()
{
	DrawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance().GetRenderer(), 255, 255, 255, 255);
}

// Updates every frame with whatever code is in here
void PlayScene::Update()
{
	UpdateDisplayList();
	b2Vec2 camPos = m_pPlayer->GetRigidBody()->GetPosition();
	Camera::Instance().SetPosition(camPos);
}

// When we are cleaning up the scene, preparing to leave
void PlayScene::Clean()
{
	RemoveAllChildren();
}

// Handle any input/other events that may happen
void PlayScene::HandleEvents()
{
	EventManager::Instance().Update();



	if (SDL_NumJoysticks() < 1)
		//CHANGE TO BOX2D PHYSICS 
	{
		if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_SPACE))
		{
			m_pPlayer->MoveAtMouse();
		}
	}
	if(EventManager::Instance().MousePressed(1)) //left mouse button
	{
		m_pProjectile = new Projectile(m_pPlayer);
		AddChild(m_pProjectile);
		m_pProjVec.push_back(m_pProjectile);
	}

	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance().Quit();
	}

	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_1))
	{
		Game::Instance().ChangeSceneState(SceneState::START);
	}

	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_2))
	{
		Game::Instance().ChangeSceneState(SceneState::END);
	}
}


// Just a getter for the RigidBody
b2Body* PlayScene::GetRigidBody()
{
	return m_rigidBody;
}