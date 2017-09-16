#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Globals.h"

class Deck {
	public:
	static std::vector<Card> current_deck;

	static int size;
			
	Deck();
	static void resetDeck();
	static void fillDeck();
	static void shuffle();
	static Card draw();
};

#endif // DECK_H
