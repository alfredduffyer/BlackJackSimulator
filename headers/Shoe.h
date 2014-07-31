#include <stdio.h>
#include <stdlib.h>
#include "_variables.h"
#include "_config.h"
#include "functions.h"
#include "print.h"
#include "Card.h"
#include "GlobalCount.h"
#include "Hand.h"

#ifndef SHOE_H
#define SHOE_H

class Shoe
{
	private:
		Card* cards;		// Cards contained in the shoe
		int size;		// Shoe size, in number of cards
		int topIndex;		// The index of the next card to be used
		int dealingLimit;	// The number of cards after which the dealer shuffles the shoe
	
	public:
		Shoe(int size);		// Calls create
		void create();		// Generate a shoe composed of as many decks as stored in the attribute size
		void shuffle();		// Shuffles the shoe randomly
		void burn();		// Burns the first cards
		void reset();		// Resets the shoe (shuffle, burn)
		void print();		// Prints the shoe's content in the console
		int getSize();		// Gives the shoe's size
		int getLimit();		// Gives the shoe's dealing limit
		int getIndex();		// Gives the top index
		bool isTheEnd();	// true if the dealing limit has been passed and the shoe must be shuffled, false otherwise
		Card top();		// Gives the next card to be dealt, and updates the top index
};

#endif
