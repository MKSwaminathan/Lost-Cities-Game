
#define NUM_COLORS 5

typedef enum CardColor { 
  YELLOW = 0, 
  BLUE, 
  WHITE, 
  GREEN, 
  RED
} CardColor;

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
