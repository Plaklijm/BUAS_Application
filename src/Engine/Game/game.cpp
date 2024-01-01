#include "game.h"

#include <string>
#include <fstream>

#include "MenuState.h"
#include "PlayState.h"
#include "../src/Player/InputManager.h"
#include "../surface.h"

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		game_input = InputManager::Instance();
		ChangeState(new PlayState());
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		// Cleanup all the states
		while (!states.empty())
		{
			states.back()->Exit();
			states.pop_back();
		}
		
		InputManager::Release();
		game_input = nullptr;
	}
	
	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	float dt;
	void Game::Tick(float deltaTime)
	{
		game_input->Update();
		dt = deltaTime;
		states.back()->Update(deltaTime);

		if (game_input->KeyDown(SDL_SCANCODE_P))
		{
			PushState(new MenuState());
		}

		if (game_input->KeyReleased(SDL_SCANCODE_P))
		{
			PopState();
		}

		// Update the game input, it will be read from the states but this will keep it up to date
		game_input->UpdatePrevInput();
	}
	
	
	void Game::PhysTick(float physDeltaTime) const
	{
		states.back()->PhysUpdate(physDeltaTime);
	}
	
	void Game::Render() const
	{
		// clear the graphics window
		screen->Clear(0);
		
		// log the current FPS
		std::string fps = "Current FPS: " + std::to_string(1.0f / dt);
		char *cfps = new char[fps.length() + 1];
		strcpy(cfps, fps.c_str());
		screen->Print(cfps, 2, 2, 0xffffff);
		delete [] cfps;
		
		// Render
		for (const auto state : states)
		{
			// Renders all states, done this way to display the game world behind the pauseMenu state
			state->Render(screen);
		}
	}

	void Game::ChangeState(State* state)
	{
		if (!states.empty())
		{
			states.back()->Exit();
			states.pop_back();
		}

		states.push_back(state);
		states.back()->Init();
	}

	// pushes a state onto the current one
	void Game::PushState(State* state)
	{
		// Pause the current active state
		if (!states.empty())
		{
			states.back()->Pause();
		}

		// Push the state and initialize it
		states.push_back(state);
		states.back()->Init();
	}

	void Game::PopState()
	{
		if (!states.empty())
		{
			states.back()->Exit();
			states.pop_back();
		}

		if (!states.empty())
		{
			states.back()->Continue();
		}
	}
};
