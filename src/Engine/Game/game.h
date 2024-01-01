#pragma once
#include <vector>

#include "State.h"


class InputManager;

namespace Tmpl8 {

class Game
{
public:
	void SetTarget( Surface* surface ) { screen = surface; }
	
	void Init();
	void Shutdown();
	
	void Tick( float deltaTime );
	void PhysTick(float physDeltaTime) const; // sounds like visstick
	void Render() const;

	void ChangeState(State* state);
	void PushState(State* state);
	void PopState();
	
private:
	std::vector<State*> states;
	
	Surface* screen;
	InputManager* game_input = nullptr;

};

}; // namespace Tmpl8