#pragma once
#ifndef __GAME__
#define __GAME__

// Core Libraries
#include <iostream>
#include <string>
#include <vector>
#include "SceneState.h"

#include <SDL.h>

// Game Managers
#include "CollisionManager.h"

// Scenes
#include "StartScene.h"
#include "PlayScene.h"
#include "LPScene.h"
#include "L1Scene.h"
#include "L2Scene.h"
#include "L3Scene.h"
#include "LBScene.h"
#include "EndScene.h"
#include "WHATScene.h"
#include "OPPScene.h"

#include "Config.h"

#include "ImGuiWindowFrame.h"

class Game
{
public:
	static Game& Instance()
	{
		static Game instance;
		return instance;
	}

	// simply set the isRunning variable to true
	void Init();
	bool Init(const char* title, int x, int y, int width, int height, bool fullscreen);

	// public life cycle functions
	void Render() const;
	void Update() const;
	void HandleEvents() const;
	void Clean() const;
	void Start();
	void Quit();

	// getter and setter functions
	[[nodiscard]] glm::vec2 GetMousePosition() const;

	void SetFrames(Uint32 frames);
	[[nodiscard]] Uint32 GetFrames() const;

	[[nodiscard]] float GetDeltaTime() const;
	void SetDeltaTime(float time);

	[[nodiscard]] bool IsRunning() const;
	void ChangeSceneState(SceneState new_state);

	[[nodiscard]] SDL_Window* GetWindow() const;

	bool GetDebugMode() const;
	void SetDebugMode(bool mode);

	Player* GetPlayer() const;
	void SetPlayer(Player* player);

	glm::vec4 GetLevelBoundaries();
	void SetLevelBoundaries(glm::vec4 bounds);

	// Public screen width / height variables

private:
	Game();
	~Game();

	// game properties
	bool m_bRunning;
	bool m_DebugMode;
	Uint32 m_frames;
	float m_deltaTime{};
	glm::vec2 m_mousePosition;
	Player* m_pPlayer;

	// scene variables
	Scene* m_pCurrentScene;
	SceneState m_currentSceneState;
	glm::vec4 m_levelBoundaries;

	// storage structures
	std::shared_ptr<SDL_Window> m_pWindow;
};

static int SCREEN_WIDTH;
static int SCREEN_HEIGHT;

#endif /* defined (__GAME__) */

