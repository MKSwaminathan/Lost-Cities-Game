#include <iostream>
#include "GlobalGameState.h"
#include "Deck.h"
#include <stdio.h>

// c++ inits
int GlobalGameState::deck_size;
int GlobalGameState::human_score;
int GlobalGameState::ai_score;

std::vector< std::vector<Card> > GlobalGameState::human_columns(0, std::vector<Card>(0));
std::vector< std::vector<Card> > GlobalGameState::ai_columns(0, std::vector<Card>(0));
std::vector< std::vector<Card> > GlobalGameState::discard_piles(0, std::vector<Card>(0));
std::vector<Card> GlobalGameState::human_hand(0);
std::vector<Card> GlobalGameState::ai_hand(0);

// draw to console functions

char get_color(CardColor color) {

	if (color == YELLOW) {
	
		return 'Y';
	}

	else if (color == BLUE) {
	
		return 'B';
	}

	else if (color == WHITE) {
	
		return 'W';
	}

	else if (color == GREEN) {
	
		return 'G';
	}

	else if (color == RED) {
	
		return 'R';
	}

	else {
	
		return NULL;
	}
}

CardColor get_card_color(int x) {

	if (x == 0) {

		return YELLOW;
	}

	else if (x == 1) {

		return BLUE;
	}

	else if (x == 2) {

		return WHITE;
	}

	else if (x == 3) {

		return GREEN;
	}

	else if (x == 4) {

		return RED;
	}

	else {
	
		return YELLOW;
	}

}

void GlobalGameState::draw_to_console() {

	int x,y;
	char color;
	
	std::cout << "*  *  *  *  *  *  *" << std::endl;
	
	// output ai columns
	for (x = 0; x < 12; x++) {
	
		std::cout << "*  ";
		for (y = 0; y < 5; y++) {
			
			color = get_color(get_card_color(y));
			
			if (GlobalGameState::ai_columns[y].size() >= 12 - x) {
			
				std::cout << color << GlobalGameState::ai_columns[y][12 - x].value;

				if (GlobalGameState::ai_columns[y][12 - x].value < 10) {
				
					std::cout << " ";
				}
			}

			else {
			
				std::cout << "   ";
			}
		}
		std::cout << "*" << std::endl;
	}

	// output deck size
	std::cout << "*  *  *  *  *  *  *" << std::endl;
	std::cout << "*        " << GlobalGameState::deck_size;
	if (GlobalGameState::deck_size < 10) {
		std::cout << " ";
	}
	std::cout << "       *" << std::endl;
	std::cout << "*  *  *  *  *  *  *" << std::endl;

	// output player columns
	for (x = 0; x < 12; x++) {

		std::cout << "*  ";
		for (y = 0; y < 5; y++) {

			color = get_color(get_card_color(y));
			
			if (GlobalGameState::human_columns[y].size() > x) {

				std::cout << color << GlobalGameState::human_columns[y][x].value;

				if (GlobalGameState::human_columns[y][x].value < 10) {

					std::cout << " ";
				}
			}

			else {

				std::cout << "   ";
			}
		}
		std::cout << "*" << std::endl;
	}
	std::cout << "*  *  *  *  *  *  *" << std::endl << std::endl;

	// output discard
	std::cout << "Discard:" << std::endl;
	for (x = 0; x < 5; x++) {
	
		for (y = 0; y < GlobalGameState::discard_piles[x].size(); y++) {
		
			std::cout << GlobalGameState::discard_piles[x][y].value << " ";
		}

		std::cout << std::endl;
	}
	std::cout << std::endl;
	
	// output hand
	std::cout << "Hand:" << std::endl;
	for (x = 0; x < 8; x++) {
		
		color = get_color(GlobalGameState::human_hand[0].color);
		
		std::cout << color << GlobalGameState::human_hand[x].value << " ";
	}
	std::cout << std::endl;
}

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


