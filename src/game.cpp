#include "game.h"

#include <bitset>

#include "surface.h"
#include <cstdio> //printf
#include <string>

#include "template.h"

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		
	}
	
	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------

	Sprite testSprite(new Surface("assets/player/inhale_float.png"), 6);
	
	void Game::Tick(float deltaTime)
	{
		// clear the graphics window
		screen->Clear(0);

		// log the current FPS
		std::string fps = "Current FPS: " + std::to_string(1.0f / deltaTime);
		char *cfps = new char[fps.length() + 1];
		strcpy(cfps, fps.c_str());
		screen->Print(cfps, 2, 2, 0xffffff);
		delete [] cfps;
		
		// print something to the text window
		//printf("this goes to the console window.\n");

		// Update the game logic
		GameTick(deltaTime);
		
		// Render the game
		Render();
	}

	void Game::GameTick(float dt)
	{
		/*
		player->Update(deltaTime, screen);*/
		testSprite.Draw(screen, 100, 100);
	}

	void Game::Render()
	{
	}

	void Game::KeyUp(int key)
	{
		printf("%i\n", key);
	}

	void Game::KeyDown(int key)
	{
		printf("%i\n", key);
	}

	void Game::ControllerJoystick(vec2 input)
	{
		//printf("X=%f Y=%f\n", input.x, input.y);
	}
};
