#include <iostream>
#include <string>
#include "SessionFlow.h"

void BeginHumanAISession() {
	std::cout << "BEGIN HUMAN VERSUS AI SESSION" << std::endl;
}

void BeginHumanHumanSession() {
	std::cout << "BEGIN HUMAN VERSUS HUMAN SESSION" << std::endl;
	int tmp_hand = 0;
	int* handNum = &tmp_hand;
	int move; 
	bool valid;
	Card card_to_play;
	
	while(1) {
		// PLAYER 1 TURN 
		std::cout << "----- PLAYER 1 TURN -----" << std::endl;
		draw_to_console(HUMAN2, HUMAN);
		while(1) { 
			card_to_play = prompt_init_move(HUMAN, handNum);
			std::cout << "Do you want to play or discard your card? Enter 0 to play or 1 to discard: ";
			std::cin >> move;
			if (move == 0) {
				std::cout << "playing card..." << std::endl;
				valid = GlobalGameState::play_card(HUMAN, card_to_play, *handNum);
				if (!valid) {
					std::cout << "Invalid move. Either you attempted to play a wager after you have already played a numbered card or your numbered card is not in ascending order of value. Try again..." << std::endl;
					continue; 	
				} else break;
			}
			else if (move == 1) {
				std::cout << "discarding card..." << std::endl;
				GlobalGameState::discard(HUMAN, card_to_play, *handNum);
				break;
			}
		}
		draw_to_console(HUMAN2, HUMAN);
		prompt_end_move(HUMAN, card_to_play.color);
		draw_to_console(HUMAN2, HUMAN);
		std::cout << "----- END OF PLAYER 1 TURN -----" << std::endl << std::endl;
		if (Deck::size == 0) break;
		// END OF PLAYER 1 MOVE

	
		// PLAYER 2 TURN
		std::cout << "----- PLAYER 2 TURN -----" << std::endl;
		draw_to_console(HUMAN2, HUMAN2);
		while(1) { 
			card_to_play = prompt_init_move(HUMAN2, handNum);
			std::cout << "Do you want to play or discard your card? Enter 0 to play or 1 to discard: ";
			std::cin >> move;
			if (move == 0) {
				std::cout << "playing card..." << std::endl;
				valid = GlobalGameState::play_card(HUMAN2, card_to_play, *handNum);
				if (!valid) {
					std::cout << "Invalid move. Either you attempted to play a wager after you have already played a numbered card or your numbered card is not in ascending order of value. Try again..." << std::endl;
					continue; 	
				} else break;
			}
			else if (move == 1) {
				std::cout << "discarding card..." << std::endl;
				GlobalGameState::discard(HUMAN2, card_to_play, *handNum);
				break;
			}
		}
		draw_to_console(HUMAN2, HUMAN2);
		prompt_end_move(HUMAN2, card_to_play.color);
		draw_to_console(HUMAN2, HUMAN2);
		std::cout << "----- END OF PLAYER 2 TURN -----" << std::endl << std::endl;
		if (Deck::size == 0) break;
		// END OF PLAYER 2 MOVE
	}
}

// validity checks: valid card and card present in player hand
Card prompt_init_move(Player current_player, int* handNum) {
	std::string chosen_card;
	CardColor tmp_current = YELLOW;
	CardColor* current_color = &tmp_current;
	int tmp_wager = 0;
	int* wager_value = &tmp_wager;  
	*handNum = 0;
	

	while(1) {
		while (1) {
			std::cout << "Choose a card you want to play or discard: \n";
			std::getline (std::cin,chosen_card);
			if (chosen_card == "") {
				std::cout << "\x1b[A";
				std::cout << "\r";
				continue;
			} else break;
		}
		ErrType err = inputErr(current_player, chosen_card, current_color, wager_value, handNum);
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

void prompt_end_move(Player current_player, CardColor color_just_played) {
	int move, error;
	while (1) {
		std::cout << "Choose an option: \n 1. draw from deck \n 2. draw from Yellow discard \n 3. draw from Blue discard \n 4. draw from White discard \n 5. draw from Green discard \n 6. draw from Red discard " << std::endl;
		std::cin >> move;
		switch (move) {
			case (1):
				GlobalGameState::draw_from_deck(current_player);
				error = 0;
				break;
			case (2):
				if (GlobalGameState::discard_piles[YELLOW].empty()) {
					std::cout << "Invalid move. The discard pile you chose is empty. Try again." << std::endl;
					error = 1; break;
				}
				if (color_just_played == YELLOW) {
					std::cout << "Invalid move. You cannot draw from the dicard pile you just played to. Try again." << std::endl;
					error = 1; 
				} else {
					GlobalGameState::draw_from_discard(current_player, YELLOW);
					std::cout << "drawing from yellow discard..." << std::endl;
					error = 0;
				}		
				break;

			case (3):
				if (GlobalGameState::discard_piles[BLUE].empty()) {
					std::cout << "Invalid move. The discard pile you chose is empty. Try again." << std::endl;
					error = 1; break;
				}
				if (color_just_played == BLUE) {
					std::cout << "Invalid move. You cannot draw from the dicard pile you just played to. Try again." << std::endl;
					error = 1; 

				} else {
					GlobalGameState::draw_from_discard(current_player, BLUE);
					std::cout << "drawing from blue discard..." << std::endl;
					error = 0;
				}		

				break;

			case (4):
				if (GlobalGameState::discard_piles[WHITE].empty()) {
					std::cout << "Invalid move. The discard pile you chose is empty. Try again." << std::endl;
					error = 1; break;
				}

				if (color_just_played == WHITE) {
					std::cout << "Invalid move. You cannot draw from the dicard pile you just played to. Try again." << std::endl;
					error = 1; 
				} else {
					GlobalGameState::draw_from_discard(current_player, WHITE);
					std::cout << "drawing from white discard..." << std::endl;
					error = 0;
				}		
				break;

			case (5):
				if (GlobalGameState::discard_piles[GREEN].empty()) {
					std::cout << "Invalid move. The discard pile you chose is empty. Try again." << std::endl;
					error = 1; break;
				}

				if (color_just_played == GREEN) {
					std::cout << "Invalid move. You cannot draw from the dicard pile you just played to. Try again." << std::endl;
					error = 1; 
				} else {
					GlobalGameState::draw_from_discard(current_player, GREEN);
					std::cout << "drawing from green discard..." << std::endl;
					error = 0;
				}		
				break;

			case (6):
				if (GlobalGameState::discard_piles[RED].empty()) {
					std::cout << "Invalid move. The discard pile you chose is empty. Try again." << std::endl;
					error = 1; break;
				}

				if (color_just_played == RED) {
					std::cout << "Invalid move. You cannot draw from the dicard pile you just played to. Try again." << std::endl;
					error = 1; 
				} else {
					GlobalGameState::draw_from_discard(current_player, RED);
					std::cout << "drawing from red discard..." << std::endl;
					error = 0;
				}		
				break;

			default: 
				error = 1;
				std::cout << "Error. " << move << " is not a valid option. Try again." << std::endl;
		}
		if (error) continue;
		else if (!error) break;
	}
		
}

ErrType inputErr(Player current_player, std::string chosen_card, CardColor* current_color, int* wager_value, int* handNum){
	// check if at least 2 char
	if (chosen_card.size() < 2) return INPUT;

	// check Yellow
	if (chosen_card.substr(0,1) == "Y") {
		*current_color = YELLOW;
		if (chosen_card.substr(1,chosen_card.size()-1) == "wg" && isInHand(current_player, YELLOW, 0, wager_value, handNum)) return NONE;
		else if (std::stoi(chosen_card.substr(1,chosen_card.size()-1)) <= 10 && std::stoi(chosen_card.substr(1,chosen_card.size()-1)) > 1) { 
			if (isInHand(current_player, YELLOW, std::stoi(chosen_card.substr(1,chosen_card.size()-1)), wager_value, handNum)) return NONE;
			else return CARD;
		} else return CARDVALUE;	
	}	
	// check Blue
	else if (chosen_card.substr(0,1) == "B") {
		*current_color = BLUE;	
		if (chosen_card.substr(1,chosen_card.size()-1) == "wg" && isInHand(current_player, BLUE, 0, wager_value, handNum)) return NONE;
		else if (std::stoi(chosen_card.substr(1,chosen_card.size()-1)) <= 10 && std::stoi(chosen_card.substr(1,chosen_card.size()-1)) > 1) { 
			if (isInHand(current_player, BLUE, std::stoi(chosen_card.substr(1,chosen_card.size()-1)), wager_value, handNum)) return NONE;
			else return CARD;
		} else return CARDVALUE;	

	}
	// check White
	else if (chosen_card.substr(0,1) == "W") {
		*current_color = WHITE;
		if (chosen_card.substr(1,chosen_card.size()-1) == "wg" && isInHand(current_player, WHITE, 0, wager_value, handNum)) return NONE;
		else if (std::stoi(chosen_card.substr(1,chosen_card.size()-1)) <= 10 && std::stoi(chosen_card.substr(1,chosen_card.size()-1)) > 1) { 
			if (isInHand(current_player, WHITE, std::stoi(chosen_card.substr(1,chosen_card.size()-1)), wager_value, handNum)) return NONE;
			else return CARD;
		} else return CARDVALUE;	

	}	
	// check Green
	else if (chosen_card.substr(0,1) == "G") {
		*current_color = GREEN;
		if (chosen_card.substr(1,chosen_card.size()-1) == "wg" && isInHand(current_player, GREEN, 0, wager_value, handNum)) return NONE;
		else if (std::stoi(chosen_card.substr(1,chosen_card.size()-1)) <= 10 && std::stoi(chosen_card.substr(1,chosen_card.size()-1)) > 1) { 
			if (isInHand(current_player, GREEN, std::stoi(chosen_card.substr(1,chosen_card.size()-1)), wager_value, handNum)) return NONE;
			else return CARD;
		} else return CARDVALUE;	

	}
	// check Red
	else if (chosen_card.substr(0,1) == "R") {
		*current_color = RED;
		if (chosen_card.substr(1,chosen_card.size()-1) == "wg" && isInHand(current_player, RED, 0, wager_value, handNum)) return NONE;
		else if (std::stoi(chosen_card.substr(1,chosen_card.size()-1)) <= 10 && std::stoi(chosen_card.substr(1,chosen_card.size()-1)) > 1) { 
			if (isInHand(current_player, RED, std::stoi(chosen_card.substr(1,chosen_card.size()-1)), wager_value, handNum)) return NONE;
			else return CARD;
		} else return CARDVALUE;	

	} 
	// invalid color
	else { return COLOR; }
		
}

bool isInHand(Player current_player, CardColor current_color, int current_value, int* wager_value, int* handNum){
	if (current_player == HUMAN) {
		for (int idx = 0; idx < HAND_SIZE; idx++) {
			if (GlobalGameState::human_hand[idx].color == current_color && GlobalGameState::human_hand[idx].value == current_value) {
				*handNum = idx;
				return true;
			}
			else if (current_value == 0 && (GlobalGameState::human_hand[idx].value == 11 || \
											GlobalGameState::human_hand[idx].value == 12 || \
											GlobalGameState::human_hand[idx].value == 13)) {
				*handNum = idx;
				*wager_value = GlobalGameState::human_hand[idx].value;
				return true;
			}
		} return false;
	} else if (current_player == HUMAN2) {	
		for (int idx = 0; idx < HAND_SIZE; idx++) {
			if (GlobalGameState::human2_hand[idx].color == current_color && GlobalGameState::human2_hand[idx].value == current_value) {
				*handNum = idx;
				return true;
			}
			else if (current_value == 0 && (GlobalGameState::human2_hand[idx].value == 11 || \
											GlobalGameState::human2_hand[idx].value == 12 || \
											GlobalGameState::human2_hand[idx].value == 13)) {
				*handNum = idx;
				*wager_value = GlobalGameState::human2_hand[idx].value;
				return true;
			}
		} return false;
	} else if (current_player == AI) {
		for (int idx = 0; idx < HAND_SIZE; idx++) {
			if (GlobalGameState::ai_hand[idx].color == current_color && GlobalGameState::ai_hand[idx].value == current_value) {
				*handNum = idx;
				return true;
			}
			else if (current_value == 0 && (GlobalGameState::ai_hand[idx].value == 11 || \
											GlobalGameState::ai_hand[idx].value == 12 || \
											GlobalGameState::ai_hand[idx].value == 13)) {
				*wager_value = GlobalGameState::ai_hand[idx].value;
				return true;
			}
		} return false;
	} return false;
}
