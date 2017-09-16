#ifndef GLOBALS_H
#define GLOBALS_H

#define NUM_TOTAL_CARDS 60
#define NUM_COLORS 5
#define NUM_CARDS_PER_COLOR 12

typedef enum CardColor { 
  YELLOW = 0, 
  BLUE, 
  WHITE, 
  GREEN, 
  RED
} CardColor;

typedef struct Card {
	int value;
	CardColor color;
} Card;


#endif // GLOBALS_H
