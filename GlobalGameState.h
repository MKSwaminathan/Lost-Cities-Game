#include <vector>
#include "Globals.h"


class GlobalGameState {
	public:
	static std::vector< std::vector<Card> > player_columns;
	static std::vector< std::vector<Card> > ai_columns;
	static std::vector< std::vector<Card> > discard_piles;

	static std::vector<Card> player_hand;
	static std::vector<Card> ai_hand;

	static int deck_size;

	GlobalGameState();
	static int getDeckSize();
};

