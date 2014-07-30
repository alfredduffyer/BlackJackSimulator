#include <stdio.h>
#include <stdlib.h>
#include "_variables.h"
#include "_config.h"
#include "functions.h"
#include "print.h"
#include "Card.h"
#include "GlobalCount.h"
#include "Hand.h"
#include "Shoe.h"
#include "System.h"

#ifndef SYSTEM_TEN_COUNT_H
#define SYSTEM_TEN_COUNT_H

class System_TenCount : public System
{
	private:
		
	
	public:
		System_TenCount();
		void initiate_hardStandingNumbers();	// Fills the Hard Standing Numbers table
		void initiate_softStandingNumbers();	// Fills the Soft Standing Numbers table
		void initiate_hardDoublingDown();		// Fills the Hard Doubling Down table
		void initiate_softDoublingDown();		// Fills the Hard Doubling Down table
		void initiate_splittingPairs();			// Fills the Splitting Pairs table
		void initiateTables();					// Calls the initiate_xxx methods
		virtual void updateComparator();			// Updates the comparator according to the counting numbers
		virtual int howManyHands(int maxHands);		// Calculates how many hands the player should be playing for a turn
		virtual int bet();							// Calculates how many units the player should be betting for a turn
		virtual bool insure();						// true if the player should insure, false otherwise
		virtual bool draw(int player, int dealer, bool soft);			// true if the player should draw a card, false otherwise
		virtual bool doubleDown(int player, int dealer, bool soft);		// true if the player should double down, false otherwise
		virtual bool split(int player, int dealer);						// true if the player should split his pair, false otherwise
		virtual int exception(Hand* player, Hand* dealer, bool canSplit, bool canDoubleDown);		// Gives a decision if there is an exception with the situation, 0 otherwise
};

#endif
