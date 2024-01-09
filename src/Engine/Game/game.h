#pragma once
#include <vector>
#include "../InputManager.h"
#include "../SoundManager.h"

class State;

namespace Tmpl8 {
	
class Surface;

class Game
{
public:
	Game();
	
	void SetTarget( Surface* surface ) { screen = surface; }
	
	void Init(bool fullscreen, float windowX, float windowY);
	void Shutdown();
	
	void Tick( float deltaTime );
	void PhysTick(float physDeltaTime) const; // sounds like visstick :)
	void Render() const;

	void ChangeState(State* state);
	void PushState(State* state);
	void PopState();

	// Moved in here to have control over it in the gameStates
	int GetExitApp() const {
		return exitApp;
	}
	void SetExitApp(int i) {
		exitApp = i;
	}
		
private:
	int exitApp;
	std::vector<State*> states;
	
	Surface* screen;
	InputManager* gameInput = nullptr;
	SoundManager* soundManager = nullptr;

};

}; // namespace Tmpl8