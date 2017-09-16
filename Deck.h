#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Globals.h"

class Deck {
	public:
	static std::vector< std::vector<bool> > possible_cards_mask;
	static std::vector<Card> current_deck;

	static int size;
			
	Deck();
	static void initPossibleCardsMask();
	static void shuffle();
	static Card draw();
};

#endif // DECK_H
