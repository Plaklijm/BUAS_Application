#include "include/game.h"

#include <bitset>

#include "include/surface.h"
#include <cstdio> //printf
#include <string>

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
	unsigned int frame = 0;
	float animationTime;
	float animationSpeed = .1f;
	
	void Game::Tick(float deltaTime)
	{
		std::string fps = "Current FPS: " + std::to_string((1.0f / deltaTime));
		// clear the graphics window
		screen->Clear(0);
		// print something in the graphics window
		screen->Print("hello world", 10, 2, 0xffffff);
		// print something to the text window
		printf("this goes to the console window.\n");
		

		/*
		player->Update(deltaTime, screen);
		animationTime += deltaTime;
		if (animationTime >= animationSpeed)
		{
			animationTime = 0;
			testSprite.SetFrame(frame);
			frame++;
			if (frame >= testSprite.Frames()) { frame = 0; }
		}
		testSprite.Draw(screen, 100, 100);*/
	}

	void Game::KeyUp(int key)
	{
		
	}

	void Game::KeyDown(int key)
	{
		
	}
};
