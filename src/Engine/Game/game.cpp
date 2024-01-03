#include "game.h"

#include <string>
#include <fstream>

#include "MainMenuState.h"
#include "PauseState.h"
#include "PlayState.h"
#include "../src/Engine/InputManager.h"
#include "../surface.h"

namespace Tmpl8
{
	Game::Game() : exitApp(0)
	{
		isPlaying = false;
		isPaused = false;
	}

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	//Sprite testSprite = Sprite(new Surface(), 18);
	void Game::Init(bool fullscreen, float windowX, float windowY)
	{
		game_input = InputManager::Instance();
		game_input->SetWindowParams(fullscreen, windowX, windowY);
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
		game_input = nullptr;
	}
	
	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	float dt;
	void Game::Tick(float deltaTime)
	{
		game_input->Update();
		
		// Only for logging the FPS
		dt = deltaTime;

		// Update the current state
		states.back()->Update(deltaTime);

		if (game_input->KeyDown(SDL_SCANCODE_ESCAPE) && isPlaying)
		{
			PushState(PauseState::Instance());
		}
		else if (game_input->KeyDown(SDL_SCANCODE_ESCAPE) && isPaused)
		{
			PopState();
		}

		// Update the game input, it will be read from the states but this will keep it up to date
		game_input->UpdatePrevInput();
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
		// Pause the current active state
		if (!states.empty())
		{
			states.back()->Pause();
		}

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

		if (!states.empty())
		{
			// Resume old state
			states.back()->Continue();
		}
	}
}
