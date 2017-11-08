#include <iostream>
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

void draw_to_console() {
	int x,y;
	char color;
	std::cout << std::endl;
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
		color = get_color(get_card_color(x));
		for (y = 0; y < GlobalGameState::discard_piles[x].size(); y++) {
			std::cout << color << GlobalGameState::discard_piles[x][y].value << " ";
		}

		std::cout << std::endl;
	}
	std::cout << std::endl;
	
	// output hand
	std::cout << "Hand:" << std::endl;
	for (x = 0; x < 8; x++) {
		color = get_color(GlobalGameState::human_hand[x].color);
		std::cout << color << GlobalGameState::human_hand[x].value << " ";
	}
	std::cout << std::endl;
}

// player turn functions
int card_choice() {
	int choice;
	while (1) {
		std::cout << "Which card in your hand?" << std::endl;
		std::cin >> choice;
		if (choice > 0 && choice < 9) {
			return choice - 1;
		}
		else {
			std::cout << "That is not a valid choice." << std::endl;
		}
	}
}

void player_turn() {
	int choice, card;
	while (1) {
		std::cout << std::endl;
		std::cout << "Do you want to play(0) or discard(1) a card?" << std::endl;
		std::cin >> choice;
		if (choice == 0) {
			card = card_choice();
			GlobalGameState::play_card(HUMAN, GlobalGameState::human_hand[card], card);
			GlobalGameState::draw_from_deck(HUMAN); // need to add option to draw from discard
			draw_to_console();
			return;
		}
		else if (choice == 1) {
			card = card_choice();
			GlobalGameState::discard(HUMAN, GlobalGameState::human_hand[card], card);
			GlobalGameState::draw_from_deck(HUMAN);// need to add option to draw from discard
			draw_to_console();
			return;
		}
		else {
			std::cout << "That is not a valid choice." << std::endl;
		}
	}

}

// ai turn
void ai_turn() {
	
}
