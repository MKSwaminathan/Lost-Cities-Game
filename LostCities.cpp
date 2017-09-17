#include <iostream>
#include "GlobalGameState.h"

void InitSession() {

	GlobalGameState global_state;
	GlobalGameState::newGame();
}
int main () {
	InitSession();
	std::cout << "pls work" << std::endl;
	return 0;

}


