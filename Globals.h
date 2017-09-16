#pragma once

#define NUM_COLORS 5

typedef enum CardColor{Yellow, Blue, White, Green, Red};

typedef struct Card {

	int value;
	int color;
} Card;

Card GDeck[60];

Card Player1_Board[5][12];
Card Player2_Board[5][12];
Card Discar[5][12];

Card All_Possible[60];

int Total_Cards;
