#include "game.h"

#include <cstdio> //printf
#include <string>
#include <fstream>

#include "InputManager.h"
#include "player.h"
#include "template.h"
#include "surface.h"

namespace Tmpl8
{
	Player* player;
	Sprite testSprite(new Surface("assets/player/inhale_float.png"), 6);
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		game_input = InputManager::Instance();
		player = new Player(game_input);
		testSprite.SetFrame(1);
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		InputManager::Release();
		game_input = nullptr;
	}
	
	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		game_input->Update();
		// clear the graphics window
		screen->Clear(0);
		testSprite.Draw(screen, 0, -20);
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
		
		game_input->UpdatePrevInput();
	}
	
	void Game::GameTick(float dt)
	{
		/*
		player->Update(deltaTime, screen);*/

		player->Update(dt);
	}
	
	void Game::PhysTick(float dt)
	{
		player->UpdatePhysics(dt);
	}

	void Game::Render()
	{
		player->RenderPlayer(screen);
	}


	
	// MAYBE STILL USEFULL IN THE FUTURE

	
		/*const auto axisIt = game_input->controllerAxisMapping.find(static_cast<SDL_GameControllerAxis>(axis));

		if (axisIt != game_input->controllerAxisMapping.end())
		{
			const ActionType action = axisIt->second;
			const int value = axisValue;
			if (axis == SDL_CONTROLLER_AXIS_LEFTX)
			{
				// Handle left and right movement based on the axis value
				if (value < -DeadZone)
					player->HandleAction(ActionType::MOVE_LEFT); 
				else if (value > DeadZone)
					player->HandleAction(ActionType::MOVE_RIGHT);
				else
					player->HandleAction(ActionType::NO_MOVEMENT);
				
			}
			else if (axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT)
			{
				if (axisValue > DeadZone)
				{
					player->HandleAction(action);
				}
			}

		}*/
	
};
