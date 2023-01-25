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
#include "EndScene.h"

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
	[[nodiscard]] glm::ivec2 GetMousePosition(); //probably should move to Util

	void SetFrames(Uint32 frames);
	[[nodiscard]] Uint32 GetFrames() const;

	[[nodiscard]] float GetDeltaTime() const;
	void SetDeltaTime(float time);

	[[nodiscard]] bool IsRunning() const;
	void ChangeSceneState(SceneState new_state);

	[[nodiscard]] SDL_Window* GetWindow() const;
	int GetWindowWidth() const { return m_ScreenWidth; }
	int GetWindowHeight() const { return m_ScreenHeight; }

	
private:
	Game();

	// game properties
	bool m_bRunning;
	Uint32 m_frames;
	float m_deltaTime{};
	glm::ivec2 m_mousePosition;
	// scene variables
	Scene* m_pCurrentScene;
	SceneState m_currentSceneState;
	float timeStep = 1.0f / 60.f;
	int32 velocityIterations = 10;
	int32 positionIterations = 8;
	int m_ScreenWidth;
	int m_ScreenHeight;
	
	
	// storage structures
	std::shared_ptr<SDL_Window> m_pWindow;
};


#endif /* defined (__GAME__) */

