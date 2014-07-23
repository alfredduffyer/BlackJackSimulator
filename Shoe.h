#include <iostream>
#include <stdio.h>
#include <stdlib.h>
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
		int size;			// Shoe size, in cards
		int topIndex;		// The index of the next card to be used
		int dealingLimit;	// 
	
	public:
		// Creates a shoe of a certain size (in decks)
		Shoe(int size);
		
		// Destructor
		~Shoe();
		
		// Initiates all the cards
		void create();
		
		// Prints the shoe
		void print();
		
		// Suffles deeply the shoe
		void shuffle();
		
		// Gives the size
		int getSize();
		
		// Resets the shoe
		void reset();
		
		bool isTheEnd();
		
		// Burns the first cards, if any
		void burn();
		
		int getLimit();
		int getIndex();
		
		// Gives the next card
		Card top();
};

#endif
