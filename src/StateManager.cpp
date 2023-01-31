#include "StateManager.h"

void StateManager::Update()
{
	if (!s_states.empty()) // If the state vector is NOT empty. (always)
	{
		s_states.back()->Update(); // Invokes the Update of the "current state"
	}
}

void StateManager::Render()
{
	if (!s_states.empty())
	{
		s_states.back()->Render();
	}
}

// Used where there needs to be two states in the vector, e.g. Game and Pause.
void StateManager::PushState(State* pState)
{
	s_states.push_back(pState);
	s_states.back()->Enter(); // Enter is used for initialization.
}

void StateManager::PopState()
{
	if (s_states.size() <= 1) return; // Exit this function if there are less than two states in the vector

	s_states.back()->Exit();
	delete s_states.back();
	s_states.back() = nullptr;
	s_states.pop_back();

	s_states.back()->Resume();
}


void StateManager::ChangeState(State* pState)
{
	if (!s_states.empty()) // We're changing state with a vector with one state
	{
		s_states.back()->Exit();
		delete s_states.back();
		s_states.back() = nullptr;
		s_states.pop_back();
	}
	s_states.push_back(pState);
	s_states.back()->Enter(); // Enter is used for initialization.
}

void StateManager::Quit()
{
	while (!s_states.empty())
	{
		s_states.back()->Exit();
		delete s_states.back();
		s_states.back() = nullptr;
		s_states.pop_back();
	}
}

std::vector<State*>& StateManager::GetStates()
{
	return s_states;
}


std::vector<State*> StateManager::s_states; // Allocation purposes