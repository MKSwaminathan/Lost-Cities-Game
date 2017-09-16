#include <iostream>
#include "Deck.h"

// c++ inits
std::vector< std::vector<bool> > Deck::possible_cards_mask(0, std::vector<bool>(0));
std::vector<Card> Deck::current_deck(0);
int Deck::size;

void Deck::initPossibleCardsMask() {
	for (int i = 0; i < NUM_COLORS - 1; i++){
		for (int j = 0; j <  NUM_CARDS_PER_COLOR - 1; j++) {
			Deck::possible_cards_mask[i][j] = true;
		}
	}
}

void Deck::shuffle() {

}

Card Deck::draw(){
	Deck::size --;
	Card drawn = Deck::current_deck.back();
	Deck::current_deck.pop_back();
	return drawn;
}

Deck::Deck() {
	Deck::current_deck.resize(NUM_TOTAL_CARDS);
	Deck::possible_cards_mask.resize(NUM_COLORS, std::vector<bool>(NUM_CARDS_PER_COLOR));
	initPossibleCardsMask();
	Deck::size = NUM_TOTAL_CARDS;
}
