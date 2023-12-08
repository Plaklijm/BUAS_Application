#pragma once
#include <SDL2-2.28.5/include/SDL_stdinc.h>

class InputSystem;

namespace Tmpl8 {
	
class vec2;
class Sprite;
class Surface;

class Game
{
public:
	void SetTarget( Surface* surface ) { screen = surface; }
	void SetInput( InputSystem* system ) { game_input = system; }
	
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void GameTick(float dt);
	void PhysTick(float dt);
	void Render();
	
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove( int x, int y ) { /* implement if you want to detect mouse movement */ }
	void KeyUp( int key );
	void KeyDown( int key );
	void ButtonUp( int key ) const;
	void ButtonDown( int key );
	void Axis( int axis, Sint16 axisValue );
	void ControllerJoystick( vec2 input );

private:
	Surface* screen;
	InputSystem* game_input;
};

}; // namespace Tmpl8