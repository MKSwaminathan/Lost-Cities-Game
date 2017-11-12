#include <iostream>
#include "Console.h"

void InitSession() {

	GlobalGameState global_state(AI);
	GlobalGameState::newGameHumanAI();
	draw_to_console();
}
int main () {
	
	InitSession();
	return 0;

}


