#include "game.h"

#include "surface.h"
#include <cstdio> //printf
#include <string>

#include "player.h"
#include "template.h"

namespace Tmpl8
{


	
	Player* player;
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		player = new Player();
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
	
	void Game::PhysTick(float dt)
	{
		player->UpdatePlayer(dt);
	}

	void Game::Render()
	{
		player->RenderPlayer(screen);
	}

	void Game::KeyUp(int key)
	{
		player->KeyUpEvent(key, false);
	}

	void Game::KeyDown(int key)
	{
		player->KeyDownEvent(key, false);
	}

	void Game::ControllerJoystick(vec2 input)
	{
		//printf("X=%f Y=%f\n", input.x, input.y);
	}
};
