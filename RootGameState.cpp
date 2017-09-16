#include <iostream>
#include <globals.h>
#include <vector>

#define NUM_COLORS 5


class RootGameState{

  public:
  // player columns -- 2D color x card
  static std::vector< std::vector<Card> > player_columns;
  static std::vector< std::vector<Card> > ai_columns; 
  // discard piles
  static std::vector< std::vector<Card> > discard_piles;
  // scores
  static int player_score;
  static int ai_score;
  // deck size
  static int deck_size;
  // hands
  static Card player_hand[8];
  static Card ai_hand[8];
     
  RootGameState(); // constr.
// newgame/reset
// update root state 
// get current score
  

};

//Member fxns 
RootGameState::RootGameState() {
  
}

void RootGameState::newGame() {

}
