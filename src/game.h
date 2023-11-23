#pragma once

namespace Tmpl8 {
class Sprite;
class Surface;
class Game
{
public:
	void SetTarget( Surface* surface ) { screen = surface; }
	
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void GameTick(float dt);
	void Render();
	
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove( int x, int y ) { /* implement if you want to detect mouse movement */ }
	void KeyUp( int key );
	void KeyDown( int key );
private:
	Surface* screen;
};

}; // namespace Tmpl8