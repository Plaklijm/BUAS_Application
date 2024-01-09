#include "game.h"

#include <string>

#include "MainMenuState.h"
#include "PauseState.h"
#include "../surface.h"

namespace Tmpl8
{
	Game::Game() : exitApp(0)
	{
	}

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init(bool fullscreen, float windowX, float windowY)
	{
		gameInput = InputManager::Instance();
		gameInput->SetWindowParams(fullscreen, windowX, windowY);

		soundManager = SoundManager::Instance();
		
		ChangeState(MainMenuState::Instance());
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

		//Cleanup the input manager
		InputManager::Release();
		gameInput = nullptr;

		//Cleanup the sound system
		SoundManager::Instance()->Cleanup();
		SoundManager::Release();
		soundManager = nullptr;
	}
	
	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	float dt;
	void Game::Tick(float deltaTime)
	{
		gameInput->Update();
		
		// Only for logging the FPS
		dt = deltaTime;

		// Update the current state
		states.back()->Update(deltaTime);
		
		// Update the game input, it will be read from the states but this will keep it up to date
		gameInput->UpdatePrevInput();
	}
	
	void Game::PhysTick(float physDeltaTime) const
	{
		// Update the physics in the states
		states.back()->PhysUpdate(physDeltaTime);
	}
	
	void Game::Render() const
	{
		// clear the graphics window
		screen->Clear(0);
		
		// Render
		for (const auto state : states)
		{
			// Renders all states, done this way to display the game world behind the pauseMenu state
			state->Render(screen);
		}

		// log the current FPS
		std::string fps = "Current FPS: " + std::to_string(1.0f / dt);
		char *cfps = new char[fps.length() + 1];
		strcpy(cfps, fps.c_str());
		screen->Print(cfps, 2, 2, 0xffffff);
		delete [] cfps;
	}

	void Game::ChangeState(State* state)
	{
		while (!states.empty())
		{
			// Exit the current state and remove it from the list
			states.back()->Exit();
			states.pop_back();
		}

		// push the new state and initialize it
		states.push_back(state);
		states.back()->Init(this);
	}

	// pushes a state onto the current one
	void Game::PushState(State* state)
	{
		// Push the new state and initialize it
		states.push_back(state);
		states.back()->Init(this);
	}

	void Game::PopState()
	{
		if (!states.empty())
		{
			// Exit from the back state
			states.back()->Exit();
			states.pop_back();
		}
	}
}
