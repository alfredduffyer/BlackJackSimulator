#include "Hand.h"

#ifndef SYSTEM_H
#define SYSTEM_H

class System
{
	protected:
		double** hardStanding;		// Table ( 8 x 10) of hard standing numbers
		double** softStanding;		// Table ( 3 x 10) of soft standing numbers
		double** hardDoublingDown;	// Table (10 x 10) of hard doubling down numbers
		double** softDoublingDown;	// Table ( 9 x 10) of soft standing numbers
		double** splittingPairs;	// Table (10 x 10) of splitting pairs numbers
		double comparator;		// Number that is compared to the numbers stored in the talbes (count, other/tens, hi-lo...)
	
	public:
		System();					// Allocates the memory for the tables
		~System();					// Frees the memory from the tables
		virtual void initiateTables();			// Initiates and fills the tables
		virtual void updateComparator();		// Updates the comparator according to the counting numbers
		virtual int howManyHands(int maxHands);		// Calculates how many hands the player should be playing for a turn
		virtual int bet();				// Calculates how many units the player should be betting for a turn
		virtual bool insure();						// true if the player should insure, false otherwise
		virtual int exception(Hand* player, Hand* dealer, bool canSplit, bool canDoubleDown);		// Gives a decision if there is an exception with the situation, 0 otherwise
		virtual bool split(int player, int dealer);			// true if the player should split his pair, false otherwise
		virtual bool doubleDown(int player, int dealer, bool soft);	// true if the player should double down, false otherwise
		virtual bool draw(int player, int dealer, bool soft);		// true if the player should draw a card, false otherwise
		virtual int decision(Hand* player, Hand* dealer, bool canSplit, bool canDoubleDown);		// Takes a decision according to all the parameters of the situation
};

#endif
