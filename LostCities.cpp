#include <iostream>
#include "Console.h"
#include "SessionFlow.h"

void InitSession();

int main () {
	
	InitSession();
	BeginHumanAISession();
//	BeginHumanHumanSession();
	return 0;

}

void InitSession() {
	GlobalGameState global_state(AI);
	GlobalGameState::newGameHumanAI();
	draw_to_console(AI);
}


