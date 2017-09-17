#include <iostream>
#include "Deck.h"

// c++ inits
std::vector<Card> Deck::current_deck(0);
int Deck::size;


void Deck::fillDeck() {
	for (int i = 0; i < NUM_COLORS; i++){
		for (int j = 0; j < NUM_CARDS_PER_COLOR; j++){
			Deck::current_deck[(i*NUM_CARDS_PER_COLOR) + j].value = j + 2;
			Deck::current_deck[(i*NUM_CARDS_PER_COLOR) + j].color = (CardColor) i;
		}
	}
}
void Deck::shuffle() {
	std::random_shuffle(Deck::current_deck.begin(), Deck::current_deck.end());
}

Card Deck::draw(){
	Deck::size --;
	Card drawn = Deck::current_deck.back();
	Deck::current_deck.pop_back();
	return drawn;
}

void Deck::resetDeck() {
	Deck::current_deck.clear();
	Deck::current_deck.resize(NUM_TOTAL_CARDS);
	Deck::fillDeck();
	Deck::shuffle();
	Deck::size = NUM_TOTAL_CARDS;
}
Deck::Deck() {
	Deck::current_deck.resize(NUM_TOTAL_CARDS);
	Deck::fillDeck();
	Deck::shuffle();
	Deck::size = NUM_TOTAL_CARDS;
}
