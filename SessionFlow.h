#include "Globals.h"
#include "GlobalGameState.h"

void BeginHumanAISession();
void BeginHumanHumanSession();
Card prompt_init_move(Player current_player);
void prompt_end_move(Player current_player);
ErrType inputErr(Player current_player, std::string chosen_card, CardColor* current_color, int* wager_value);
bool isInHand(Player current_player, CardColor current_color, int current_value, int* wager_value);
