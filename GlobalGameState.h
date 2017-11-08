#include <vector>
#include "Globals.h"


class GlobalGameState {
	public:
	static std::vector< std::vector<Card> > human_columns;
	static std::vector< std::vector<Card> > ai_columns;
	static std::vector< std::vector<Card> > discard_piles;

	static std::vector<Card> human_hand;
	static std::vector<Card> ai_hand;
	static int human_score;
	static int ai_score;
	static int deck_size;

	GlobalGameState();	
	static void newGame();
	static int getDeckSize();
	// moves to update Global State
	// these functions are agnostic to the rules -- the 
	// rules determine validity of a potential move
	static Card draw_from_deck(Player plyr);
	static Card draw_from_discard(Player plyr, CardColor color);
	static void discard(Player plyr, Card discard_card, int handNum);
	static bool play_card(Player plyr, Card card_to_play, int handNum);

};

