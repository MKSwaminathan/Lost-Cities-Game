#include <iostream>
#include "GlobalGameState.h"
#include "Deck.h"

// c++ inits
int GlobalGameState::deck_size;
int GlobalGameState::human_score;
int GlobalGameState::ai_score;

std::vector< std::vector<Card> > GlobalGameState::human_columns(0, std::vector<Card>(0));
std::vector< std::vector<Card> > GlobalGameState::ai_columns(0, std::vector<Card>(0));
std::vector< std::vector<Card> > GlobalGameState::discard_piles(0, std::vector<Card>(0));
std::vector<Card> GlobalGameState::human_hand(0);
std::vector<Card> GlobalGameState::ai_hand(0);

// member fxns
int GlobalGameState::getDeckSize(){
	return Deck::size;
}

// UPDATE GLOBAL STATE FXNS --------------------------------
Card GlobalGameState::draw_from_deck(Player plyr) {
	Card drawn_card = Deck::draw(); 
	// update hands
	if (plyr == HUMAN) GlobalGameState::human_hand.push_back(drawn_card);
	else if (plyr == AI) GlobalGameState::ai_hand.push_back(drawn_card);
	return drawn_card;
}

Card GlobalGameState::draw_from_discard(Player plyr, CardColor color) {
	Card discard_draw = GlobalGameState::discard_piles[color].back();
	GlobalGameState::discard_piles[color].pop_back();
	// update hands
	if (plyr == HUMAN) GlobalGameState::human_hand.push_back(discard_draw);
	else if (plyr == AI) GlobalGameState::ai_hand.push_back(discard_draw);
	return discard_draw;
}

void GlobalGameState::discard(Player plyr, Card discard_card, int handNum) {
	GlobalGameState::discard_piles[discard_card.color].push_back(discard_card);
	if (plyr == HUMAN) GlobalGameState::human_hand.erase(GlobalGameState::human_hand.begin() + handNum);
	else if (plyr == AI) GlobalGameState::ai_hand.erase(GlobalGameState::ai_hand.begin() + handNum);	
}

bool GlobalGameState::play_card(Player plyr, Card card_to_play, int handNum) {
	bool isWager = (card_to_play.value == 11) || (card_to_play.value == 12) || (card_to_play.value == 13);
	bool firstOfType = ((plyr == AI) ? 
						( (GlobalGameState::ai_columns[card_to_play.color].back()).value > 10 || GlobalGameState::ai_columns[card_to_play.color].empty()) : 
						( (GlobalGameState::human_columns[card_to_play.color].back()).value > 10 || GlobalGameState::human_columns[card_to_play.color].empty()) );
	bool isValidPlay =  ((plyr == AI) ? 
					 ( (GlobalGameState::ai_columns[card_to_play.color].back()).value < card_to_play.value || GlobalGameState::ai_columns[card_to_play.color].empty()) :  
					 ( (GlobalGameState::human_columns[card_to_play.color].back()).value < card_to_play.value || GlobalGameState::human_columns[card_to_play.color].empty()) ); 

	if ((isWager && firstOfType) || isValidPlay) {
		if (plyr == HUMAN) {
			GlobalGameState::human_hand.erase(GlobalGameState::human_hand.begin() + handNum);
			GlobalGameState::human_columns[card_to_play.color].push_back(card_to_play);
		}	
		else if (plyr == AI) {
			GlobalGameState::ai_hand.erase(GlobalGameState::ai_hand.begin() + handNum);
			GlobalGameState::ai_columns[card_to_play.color].push_back(card_to_play);
		}
		return true;
	}
	return false;
}
//-----------------------------------------------------------
void GlobalGameState::newGame() {
	std::cout << "Starting New Game..." << std::endl;
	// clear prev game
	GlobalGameState::human_columns.clear();
	GlobalGameState::ai_columns.clear();
	GlobalGameState::discard_piles.clear();
	GlobalGameState::human_hand.clear();
	GlobalGameState::ai_hand.clear();

	// reset for new game
	GlobalGameState::human_columns.resize(NUM_COLORS, std::vector<Card>(0));
	GlobalGameState::ai_columns.resize(NUM_COLORS, std::vector<Card>(0));
	GlobalGameState::discard_piles.resize(NUM_COLORS, std::vector<Card>(0));
	
	GlobalGameState::human_hand.resize(8);
	GlobalGameState::ai_hand.resize(8);

	Deck::resetDeck();
}

GlobalGameState::GlobalGameState(){
	GlobalGameState::human_columns.resize(NUM_COLORS, std::vector<Card>(0));
	GlobalGameState::ai_columns.resize(NUM_COLORS, std::vector<Card>(0));
	GlobalGameState::discard_piles.resize(NUM_COLORS, std::vector<Card>(0));
	
	GlobalGameState::human_hand.resize(8);
	GlobalGameState::ai_hand.resize(8);

	Deck current_deck;	
	GlobalGameState::deck_size = GlobalGameState::getDeckSize(); 

}


