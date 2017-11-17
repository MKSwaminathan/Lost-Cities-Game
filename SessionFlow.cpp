#include <iostream>
#include <string>
#include "SessionFlow.h"

void BeginHumanAISession() {
	std::cout << "BEGIN HUMAN VERSUS AI SESSION" << std::endl;
}

void BeginHumanHumanSession() {
	std::cout << "BEGIN HUMAN VERSUS HUMAN SESSION" << std::endl;
	prompt_init_move(HUMAN);
}

Card prompt_init_move(Player current_player) {
	std::string chosen_card;
	CardColor* current_color;
	int tmp = 0;
	int* wager_value = &tmp;  

	while(1) {
		std::cout << "Choose a card you want to play or discard: ";
		std::getline (std::cin,chosen_card);
		ErrType err = inputErr(HUMAN, chosen_card, current_color, wager_value);
		if (err == INPUT) {
			std::cout << "Invalid input. Your input should match the format shown in your hand.Try again." << std::endl;
			continue; 	
		} else if (err == COLOR) {
			std::cout << "Not a valid color. The color should be the first letter of one of the 5 game colors. Try again." << std::endl;
			continue;
		} else if (err == CARDVALUE) {
			std::cout << "Card value not valid. Value should be 2-10 or wg for wager. Try again." << std::endl;
			continue;
		} else if (err == CARD) {
			std::cout << "That card is not in your deck. Choose a card currently present in your deck. Try again." << std::endl;
			continue;
		} else if (err == NONE) { break; }
	}
	Card card_to_play;
	card_to_play.color = *current_color;
	if (chosen_card.substr(1,chosen_card.size()-1) == "wg") {
		card_to_play.value = *wager_value;
	} else {
		card_to_play.value = std::stoi(chosen_card.substr(1,chosen_card.size()-1));
	}
	return card_to_play;
}

void prompt_end_move(Player current_player) {

}

ErrType inputErr(Player current_player, std::string chosen_card, CardColor* current_color, int* wager_value){
	// check if at least 2 char
	if (chosen_card.size() < 2) return INPUT;

	// check Yellow
	if (chosen_card.substr(0,1) == "Y") {
		*current_color = YELLOW;
		if (chosen_card.substr(1,chosen_card.size()-1) == "wg" && isInHand(current_player, YELLOW, 0, wager_value)) return NONE;
		else if (std::stoi(chosen_card.substr(1,chosen_card.size()-1)) <= 10 && std::stoi(chosen_card.substr(1,chosen_card.size()-1)) > 1) { 
			if (isInHand(current_player, YELLOW, std::stoi(chosen_card.substr(1,chosen_card.size()-1)), wager_value)) return NONE;
			else return CARD;
		} else return CARDVALUE;	
	}	
	// check Blue
	else if (chosen_card.substr(0,1) == "B") {
		*current_color = BLUE;	
		if (chosen_card.substr(1,chosen_card.size()-1) == "wg" && isInHand(current_player, BLUE, 0, wager_value)) return NONE;
		else if (std::stoi(chosen_card.substr(1,chosen_card.size()-1)) <= 10 && std::stoi(chosen_card.substr(1,chosen_card.size()-1)) > 1) { 
			if (isInHand(current_player, BLUE, std::stoi(chosen_card.substr(1,chosen_card.size()-1)), wager_value)) return NONE;
			else return CARD;
		} else return CARDVALUE;	

	}
	// check White
	else if (chosen_card.substr(0,1) == "W") {
		*current_color = WHITE;
		if (chosen_card.substr(1,chosen_card.size()-1) == "wg" && isInHand(current_player, WHITE, 0, wager_value)) return NONE;
		else if (std::stoi(chosen_card.substr(1,chosen_card.size()-1)) <= 10 && std::stoi(chosen_card.substr(1,chosen_card.size()-1)) > 1) { 
			if (isInHand(current_player, WHITE, std::stoi(chosen_card.substr(1,chosen_card.size()-1)), wager_value)) return NONE;
			else return CARD;
		} else return CARDVALUE;	

	}	
	// check Green
	else if (chosen_card.substr(0,1) == "G") {
		*current_color = GREEN;
		if (chosen_card.substr(1,chosen_card.size()-1) == "wg" && isInHand(current_player, GREEN, 0, wager_value)) return NONE;
		else if (std::stoi(chosen_card.substr(1,chosen_card.size()-1)) <= 10 && std::stoi(chosen_card.substr(1,chosen_card.size()-1)) > 1) { 
			if (isInHand(current_player, GREEN, std::stoi(chosen_card.substr(1,chosen_card.size()-1)), wager_value)) return NONE;
			else return CARD;
		} else return CARDVALUE;	

	}
	// check Red
	else if (chosen_card.substr(0,1) == "R") {
		*current_color = RED;
		if (chosen_card.substr(1,chosen_card.size()-1) == "wg" && isInHand(current_player, RED, 0, wager_value)) return NONE;
		else if (std::stoi(chosen_card.substr(1,chosen_card.size()-1)) <= 10 && std::stoi(chosen_card.substr(1,chosen_card.size()-1)) > 1) { 
			if (isInHand(current_player, RED, std::stoi(chosen_card.substr(1,chosen_card.size()-1)), wager_value)) return NONE;
			else return CARD;
		} else return CARDVALUE;	

	} 
	// invalid color
	else { return COLOR; }
		
}

bool isInHand(Player current_player, CardColor current_color, int current_value, int* wager_value){
	if (current_player == HUMAN) {
		for (int idx = 0; idx < HAND_SIZE; idx++) {
			if (GlobalGameState::human_hand[idx].color == current_color && GlobalGameState::human_hand[idx].value == current_value) return true;
			else if (current_value == 0 && (GlobalGameState::human_hand[idx].value == 11 || \
											GlobalGameState::human_hand[idx].value == 12 || \
											GlobalGameState::human_hand[idx].value == 13)) {
				*wager_value = GlobalGameState::human_hand[idx].value;
				return true;
			}
		} return false;
	} else if (current_player == HUMAN2) {	
		for (int idx = 0; idx < HAND_SIZE; idx++) {
			if (GlobalGameState::human2_hand[idx].color == current_color && GlobalGameState::human2_hand[idx].value == current_value) return true;
			else if (current_value == 0 && (GlobalGameState::human2_hand[idx].value == 11 || \
											GlobalGameState::human2_hand[idx].value == 12 || \
											GlobalGameState::human2_hand[idx].value == 13)) {
				*wager_value = GlobalGameState::human2_hand[idx].value;
				return true;
			}
		} return false;
	} else if (current_player == AI) {
		for (int idx = 0; idx < HAND_SIZE; idx++) {
			if (GlobalGameState::ai_hand[idx].color == current_color && GlobalGameState::ai_hand[idx].value == current_value) return true;
			else if (current_value == 0 && (GlobalGameState::ai_hand[idx].value == 11 || \
											GlobalGameState::ai_hand[idx].value == 12 || \
											GlobalGameState::ai_hand[idx].value == 13)) {
				*wager_value = GlobalGameState::ai_hand[idx].value;
				return true;
			}
		} return false;
	} return false;
}
