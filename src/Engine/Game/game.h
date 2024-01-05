#pragma once
#include <vector>

#include "State.h"


class SoundManager;
class InputManager;

namespace Tmpl8 {

class Game
{
public:
	Game();
	
	void SetTarget( Surface* surface ) { screen = surface; }
	
	void Init(bool fullscreen, float windowX, float windowY);
	void Shutdown();
	
	void Tick( float deltaTime );
	void PhysTick(float physDeltaTime) const; // sounds like visstick
	void Render() const;

	void ChangeState(State* state);
	void PushState(State* state);
	void PopState();

	int GetExitApp() const {
		return exitApp;
	}
	void SetExitApp(int i) {
		exitApp = i;
	}
	void SetIsPlaying(bool i) {
		isPlaying = i;
	}
	void SetIsPaused(bool i) {
		isPaused = i;
	}
	
private:
	int exitApp;

	bool isPlaying;
	bool isPaused;
	
	std::vector<State*> states;
	
	Surface* screen;
	InputManager* gameInput = nullptr;
	SoundManager* soundManager = nullptr;

};

}; // namespace Tmpl8