#pragma once
#ifndef __STATES_H__
#define __STATES_H__
#include <map>
#include <string>
#include <iostream>
#include "StateManager.h"

class StateManager;

class State // Abstract Base Class
{ // No objects of State can be created
public:
	virtual void Enter(); // Pure virtual function. No definition
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume() {}; // Considered defined for all subclasses
protected: // Private but inherited
	State() = default;
};

class TitleState : public State
{
public:
	TitleState();
	virtual void Enter(); // Pure virtual function. No definition
	virtual void Update();
	virtual void Render();
	virtual void Exit();
private:
	// Map for music track goes here
};

class GameState : public State
{
public:
	GameState();
	virtual void Enter(); // Pure virtual function. No definition
	virtual void Update();
	virtual void Render();
	virtual void Exit();

private:
};
class PauseState : public State
{
public:
	PauseState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();

};
class EndState : public State
{
public:
	EndState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();

private:
};






// This is essential for static properties. Declare them OUTSIDE their class but with class scope.

#endif