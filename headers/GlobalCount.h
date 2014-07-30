#include <stdio.h>
#include <stdlib.h>
#include "_variables.h"
#include "_config.h"
#include "functions.h"
#include "print.h"
#include "Card.h"

#ifndef GLOBALCOUNT_H
#define GLOBALCOUNT_H

class GlobalCount
{
	private:
		int count;				// Point Count (+1 / -1)
		int remainingCards;		// Number of cards unseen from the shoe
		int tens;				// Number of remaining tens in the unseen cards
		int others;				// Number of remaining non-tens in the unseen cards
	
	public:
		GlobalCount();				// Calls reset()
		void reset();				// Resets the counting numbers for when the shoe is shuffled
		void update(int value);		// Updates the counting numbers according to the card just seen
		int getCount();				// Gives the Point Count
		int getRoughCount();		// Gives a rought idea of the Hi-Lo index
		int getRemainingCards();	// Gives the remaining cards
		int getHiLoIndex();			// Gives the Hi-Lo index
		int getTens();				// Gives the number of tens remaining
		int getOthers();			// Gives the number of non-tens remaining
		double getTenCount();		// Gives the Ten Count
		void printStatus();			// Prints the status of each counting number in the console
};

#endif
