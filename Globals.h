#ifndef GLOBALS_H
#define GLOBALS_H

#define NUM_TOTAL_CARDS 60
#define NUM_COLORS 5
#define NUM_CARDS_PER_COLOR 12

/* 11, 12, 13 == wager cards */
typedef enum CardColor { 
  YELLOW = 0, 
  BLUE, 
  WHITE, 
  GREEN, 
  RED
} CardColor;

typedef enum Player {
	HUMAN = 1,
	HUMAN2 = 2,
	AI = 3
} Player; 

typedef struct Card {
	int value;
	CardColor color;
} Card;


#endif // GLOBALS_H
