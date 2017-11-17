#include <iostream>
#include <string>
#include "Console.h"

// Console functions go here
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
		return '\0';
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

void draw_to_console(Player mode) {
	int x,y,value;
	char color;
	std::cout << std::endl;
	std::cout << "**  ***  ***  ***  ***  ***  **" << std::endl;
	
	// OUTPUT MODE COLUMNS
	if (mode == AI) {
		for (x = 0; x < 12; x++) {
			std::cout << "*    ";
			for (y = 0; y < 5; y++) {
				color = get_color(get_card_color(y));
				if (GlobalGameState::ai_columns[y].size() >= 12 - x) {
					std::cout << color << GlobalGameState::ai_columns[y][12 - x].value;
	
					if (GlobalGameState::ai_columns[y][12 - x].value < 10) {
						std::cout << " ";
					}
				}
	
				else {
					std::cout << "     ";
				}
			}
			std::cout << "*" << std::endl;
		}
	}

	if (mode == HUMAN2) {
		for (x = 0; x < 12; x++) {
			std::cout << "*    ";
			for (y = 0; y < 5; y++) {
				color = get_color(get_card_color(y));
				if (GlobalGameState::human2_columns[y].size() >= 12 - x) {
					std::cout << color << GlobalGameState::human2_columns[y][12 - x].value;
	
					if (GlobalGameState::human2_columns[y][12 - x].value < 10) {
						std::cout << " ";
					}
				}
	
				else {
					std::cout << "     ";
				}
			}
			std::cout << "*" << std::endl;
		}
	}

	// OUTPUT DECK 
	std::cout << "**  ***  ***  ***  ***  ***  *** * * * * * * * *" << std::endl;
	std::cout << "*   DISCARD                   * DECK           *" << std::endl;
	std::cout << "*                             * Cards Left: " << GlobalGameState::deck_size << " *" << std::endl;
	std::cout << "*   ";
	// OUTPUT DISCARD
	for (x = 0; x < 5; x++) {
		color = get_color(get_card_color(x));
		if (GlobalGameState::discard_piles[x].size()) { 
			y = GlobalGameState::discard_piles[x].size();		
			value = GlobalGameState::discard_piles[x][y].value;
			if (value > 10) std::cout << color << "wg ";
			else if (value == 10) std::cout << color << value << " ";
			else if (value < 10) std::cout << color << value << "  ";
		} else {
			std::cout << color << "    ";
		}
	} 
	std::cout << " *                *" << std::endl;
	std::cout << "**  ***  ***  ***  ***  ***  *** * * * * * * * *" << std::endl;

	// OUTPUT PLAYER1 COLUMNS
	for (x = 0; x < 12; x++) {
		std::cout << "*    ";
		for (y = 0; y < 5; y++) {
			color = get_color(get_card_color(y));
			if (GlobalGameState::human_columns[y].size() > x) {
				std::cout << color << GlobalGameState::human_columns[y][x].value;

				if (GlobalGameState::human_columns[y][x].value < 10) {
					std::cout << " ";
				}
			}

			else {
				std::cout << "     ";
			}
		}
		std::cout << "*" << std::endl;
	}
	std::cout << "**  ***  ***  ***  ***  ***  **" << std::endl << std::endl;
	
	// NEEDS TO BE HIDDEN	
	// output hand(s)
	std::cout << "Human1 Hand:" << std::endl;
	for (x = 0; x < 8; x++) {
		color = get_color(GlobalGameState::human_hand[x].color);
		int value = GlobalGameState::human_hand[x].value;
		std::string cardValue = "value";
		if (value > 10){
			cardValue = "wg";
		}
		else {
			cardValue = std::to_string(value);
		}	
		std::cout << color << cardValue << " ";
	}
	std::cout << std::endl;
	if (mode == HUMAN2) {
		std::cout << "Human2 Hand:" << std::endl;
		for (x = 0; x < 8; x++) {
			color = get_color(GlobalGameState::human2_hand[x].color);
			int value = GlobalGameState::human2_hand[x].value;
			std::string cardValue = "value";
			if (value > 10){
				cardValue = "wg";
			}
			else {
				cardValue = std::to_string(value);
			}
			std::cout << color << cardValue << " ";
		}
	}
	if (mode == AI) {
		std::cout << "AI Hand:" << std::endl;
		for (x = 0; x < 8; x++) {
			color = get_color(GlobalGameState::ai_hand[x].color);
			int value = GlobalGameState::ai_hand[x].value;
			std::string cardValue = "value";
			if (value > 10){
				cardValue = "wg";
			}
			else {
				cardValue = std::to_string(value);
			}
			std::cout << color << cardValue << " ";
		}
	}

	std::cout << std::endl << std::endl;
}



