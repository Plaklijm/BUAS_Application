#pragma once

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
	void Render(float deltaTime);
	
private:
	class Surface* screen;
	class InputManager* game_input = nullptr;
	class World* world;

};

}; // namespace Tmpl8