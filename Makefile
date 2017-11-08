# This is the makefile for the game

CC=g++
CFLAGS=-c
HEADERS = Globals.h GlobalGameState.h Deck.h  
OBJ = LostCities.o GlobalGameState.o Deck.o Console.o

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $< 


rungame: $(OBJ)
	$(CC) -o $@  $^

 
