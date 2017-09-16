#include "GlobalGameState.h"
#include "Deck.h"

// c++ inits
int GlobalGameState::deck_size;
std::vector< std::vector<Card> > GlobalGameState::player_columns(0, std::vector<Card>(0));
std::vector< std::vector<Card> > GlobalGameState::ai_columns(0, std::vector<Card>(0));
std::vector< std::vector<Card> > GlobalGameState::discard_piles(0, std::vector<Card>(0));
std::vector<Card> GlobalGameState::player_hand(0);
std::vector<Card> GlobalGameState::ai_hand(0);

// member fxns
int GlobalGameState::getDeckSize(){
	return Deck::size;
}

GlobalGameState::GlobalGameState(){
	GlobalGameState::player_columns.resize(NUM_COLORS, std::vector<Card>(0));
	GlobalGameState::ai_columns.resize(NUM_COLORS, std::vector<Card>(0));
	GlobalGameState::discard_piles.resize(NUM_COLORS, std::vector<Card>(0));
	
	GlobalGameState::player_hand.resize(8);
	GlobalGameState::ai_hand.resize(8);

	Deck current_deck;	
	GlobalGameState::deck_size = GlobalGameState::getDeckSize(); 

}


