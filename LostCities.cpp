#include <iostream>
#include "GlobalGameState.h"

void InitSession() {

	GlobalGameState global_state;
	GlobalGameState::newGame();
	GlobalGameState::draw_to_console();
}
int main () {
	InitSession();
	std::cout << "pls work" << std::endl;
	return 0;

}


