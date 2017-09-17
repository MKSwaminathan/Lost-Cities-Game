#include <iostream>
#include "GlobalGameState.h"

void InitSession() {

	GlobalGameState global_state;
	GlobalGameState::newGame();
	GlobalGameState::draw_to_console();
}
int main () {
	
	InitSession();
	
	while (1) {
		
		GlobalGameState::player_turn();
		GlobalGameState::ai_turn();
		GlobalGameState::draw_to_console();
	}

	return 0;

}


