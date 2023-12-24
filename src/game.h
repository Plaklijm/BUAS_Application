#pragma once
#include <SDL2-2.28.5/include/SDL_render.h>

class TextureManager;

namespace Tmpl8 {

class Game
{
public:
	void SetTarget( class Surface* surface ) { screen = surface; }
	
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void GameTick(float dt);
	void PhysTick(float dt);
	void Render();
	
private:
	class Surface* screen;
	class InputManager* game_input = nullptr;
	class World* world;

	TextureManager* textureManager;

};

}; // namespace Tmpl8