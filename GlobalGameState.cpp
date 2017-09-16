#include "GlobalGameState.h"
#include "Deck.h"

int GlobalGameState::deck_size;

int GlobalGameState::getDeckSize(){
	return Deck::size;
}

GlobalGameState::GlobalGameState(){
	Deck current_deck;	
	GlobalGameState::deck_size = GlobalGameState::getDeckSize(); 

}


