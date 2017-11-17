#include <iostream>
#include "GlobalGameState.h"
#include "Deck.h"
#include <stdio.h>

// c++ inits
int GlobalGameState::deck_size;
int GlobalGameState::human_score;
int GlobalGameState::human2_score;
int GlobalGameState::ai_score;

std::vector< std::vector<Card> > GlobalGameState::human_columns(0, std::vector<Card>(0));
std::vector< std::vector<Card> > GlobalGameState::human2_columns(0, std::vector<Card>(0));
std::vector< std::vector<Card> > GlobalGameState::ai_columns(0, std::vector<Card>(0));
std::vector< std::vector<Card> > GlobalGameState::discard_piles(0, std::vector<Card>(0));
std::vector<Card> GlobalGameState::human_hand(0);
std::vector<Card> GlobalGameState::human2_hand(0);
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
	else if (plyr == HUMAN2) GlobalGameState::human2_hand.push_back(drawn_card);
	else if (plyr == AI) GlobalGameState::ai_hand.push_back(drawn_card);
	return drawn_card;
}

Card GlobalGameState::draw_from_discard(Player plyr, CardColor color) {
	Card discard_draw = GlobalGameState::discard_piles[color].back();
	GlobalGameState::discard_piles[color].pop_back();
	// update hands
	if (plyr == HUMAN) GlobalGameState::human_hand.push_back(discard_draw);
	else if (plyr == HUMAN2) GlobalGameState::human2_hand.push_back(discard_draw);
	else if (plyr == AI) GlobalGameState::ai_hand.push_back(discard_draw);
	return discard_draw;
}

// RMR: handNum must index at 0
void GlobalGameState::discard(Player plyr, Card discard_card, int handNum) {
	GlobalGameState::discard_piles[discard_card.color].push_back(discard_card);
	if (plyr == HUMAN) GlobalGameState::human_hand.erase(GlobalGameState::human_hand.begin() + handNum);
	else if (plyr == HUMAN2) GlobalGameState::human2_hand.erase(GlobalGameState::human2_hand.begin() + handNum);
	else if (plyr == AI) GlobalGameState::ai_hand.erase(GlobalGameState::ai_hand.begin() + handNum);	
}

bool GlobalGameState::play_card(Player plyr, Card card_to_play, int handNum) {
	bool isWager = (card_to_play.value == 11) || (card_to_play.value == 12) || (card_to_play.value == 13);
	// check if wager is allowed in pending play  
	bool firstOfType = false;
	if (plyr == HUMAN) {
		if (!GlobalGameState::human_columns[card_to_play.color].empty())
			firstOfType = (GlobalGameState::human_columns[card_to_play.color].back()).value > 10;
		else firstOfType = true;
	}
	else if (plyr == HUMAN2) {
		if (!GlobalGameState::human2_columns[card_to_play.color].empty())
			firstOfType = (GlobalGameState::human2_columns[card_to_play.color].back()).value > 10;
		else firstOfType = true;
	}
	else if (plyr == AI){
		if (!GlobalGameState::ai_columns[card_to_play.color].empty())
			firstOfType = (GlobalGameState::ai_columns[card_to_play.color].back()).value > 10;
		else firstOfType = true; 
	}
	// check if play is valid (i.e pending play is in increasing value)
	bool isValidPlay =  false;
	if (plyr == HUMAN) { 
		if (!GlobalGameState::human_columns[card_to_play.color].empty())
			isValidPlay = (GlobalGameState::human_columns[card_to_play.color].back()).value < card_to_play.value;
		else isValidPlay = true;
	}
	else if (plyr == HUMAN2) {
		if (!GlobalGameState::human2_columns[card_to_play.color].empty())
			isValidPlay = (GlobalGameState::human2_columns[card_to_play.color].back()).value < card_to_play.value;
		else isValidPlay = true;
	} 
	else if (plyr == AI) {
		if (!GlobalGameState::ai_columns[card_to_play.color].empty())
			isValidPlay = (GlobalGameState::ai_columns[card_to_play.color].back()).value < card_to_play.value;
		else isValidPlay = true; 
	}
	// execute play
	if ((isWager && firstOfType) || isValidPlay) {
		if (plyr == HUMAN) {
			GlobalGameState::human_hand.erase(GlobalGameState::human_hand.begin() + handNum);
			GlobalGameState::human_columns[card_to_play.color].push_back(card_to_play);
		}
		else if (plyr == HUMAN2) {
			GlobalGameState::human2_hand.erase(GlobalGameState::human2_hand.begin() + handNum);
			GlobalGameState::human2_columns[card_to_play.color].push_back(card_to_play);
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
void GlobalGameState::newGameHumanAI() {
	std::cout << "Starting New Game Human VS. AI..." << std::endl;
	int x;
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
	
	//GlobalGameState::human_hand.resize(8);
	//GlobalGameState::ai_hand.resize(8);

	Deck::resetDeck();

	// deal out starting hands
	for (x = 0; x < 8; x++) {
		GlobalGameState::draw_from_deck(HUMAN);
		GlobalGameState::draw_from_deck(AI);
	}
}

void GlobalGameState::newGameHumanHuman() {
	std::cout << std::endl << std::endl << "Starting New Game Human VS. Human..." << std::endl;
	int x;
	// clear prev game
	GlobalGameState::human_columns.clear();
	GlobalGameState::human2_columns.clear();
	GlobalGameState::discard_piles.clear();
	GlobalGameState::human_hand.clear();
	GlobalGameState::human2_hand.clear();

	// reset for new game
	GlobalGameState::human_columns.resize(NUM_COLORS, std::vector<Card>(0));
	GlobalGameState::human2_columns.resize(NUM_COLORS, std::vector<Card>(0));
	GlobalGameState::discard_piles.resize(NUM_COLORS, std::vector<Card>(0));
	
	//GlobalGameState::human_hand.resize(8);
	//GlobalGameState::ai_hand.resize(8);

	Deck::resetDeck();

	// deal out starting hands
	for (x = 0; x < 8; x++) {
		GlobalGameState::draw_from_deck(HUMAN);
		GlobalGameState::draw_from_deck(HUMAN2);
	}
}

GlobalGameState::GlobalGameState(Player mode){
	GlobalGameState::human_columns.resize(NUM_COLORS, std::vector<Card>(0));
	if (mode == AI)
		GlobalGameState::ai_columns.resize(NUM_COLORS, std::vector<Card>(0));
	else if (mode == HUMAN2)
		GlobalGameState::human2_columns.resize(NUM_COLORS, std::vector<Card>(0));
	GlobalGameState::discard_piles.resize(NUM_COLORS, std::vector<Card>(0));
	
	//GlobalGameState::human_hand.resize(8);
	//GlobalGameState::ai_hand.resize(8);

	Deck current_deck;	
	GlobalGameState::deck_size = GlobalGameState::getDeckSize(); 
}


