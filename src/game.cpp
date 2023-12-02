#include "game.h"

#include "surface.h"
#include <cstdio> //printf
#include <string>
#include <fstream>

#include "InputSystem.h"
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

	void Game::KeyUp(int key)
	{
		player->HandleAction(ActionType::NO_MOVEMENT);
	}

	void Game::KeyDown(int key)
	{
		const auto temp = game_input->keyboardButtonMapping.find(key);
		if (temp !=  game_input->keyboardButtonMapping.end()) {
			const ActionType action = temp->second;
			player->HandleAction(action);
		}
	}

	void Game::ButtonUp(int key) const
	{
		const auto temp = game_input->controllerButtonMapping.find(static_cast<SDL_GameControllerButton>(key));
		if (temp !=  game_input->controllerButtonMapping.end()) {
			const ActionType action = temp->second;
			player->HandleAction(action);
		}
	}

	void Game::ButtonDown(int key)
	{
	}

	void Game::Axis(int axis, Sint16 axisValue)
	{
		const auto axisIt = game_input->controllerAxisMapping.find(static_cast<SDL_GameControllerAxis>(axis));

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

		}
	}

	void Game::ControllerJoystick(vec2 input)
	{
		//printf("X=%f Y=%f\n", input.x, input.y);
	}
};
