#include <iostream>
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

#ifndef SYSTEM_BASIC_STRATEGY_H
#define SYSTEM_BASIC_STRATEGY_H

class System_BasicStrategy : public System
{
	private:
		
	
	public:
		System_BasicStrategy();					// Calls initiateTables
		void initiate_hardStandingNumbers();	// Fills the Hard Standing Numbers table
		void initiate_softStandingNumbers();	// Fills the Soft Standing Numbers table
		void initiate_hardDoublingDown();		// Fills the Hard Doubling Down table
		void initiate_softDoublingDown();		// Fills the Hard Doubling Down table
		void initiate_splittingPairs();			// Fills the Splitting Pairs table
		void initiateTables();					// Calls the initiate_xxx methods
		virtual int howManyHands(int maxHands);			// Calculates how many hands the player should be playing for a turn
		virtual bool insure();							// true if the player should insure, false otherwise
		virtual int exception(Hand* player, Hand* dealer, bool canSplit, bool canDoubleDown);		// Gives a decision if there is an exception with the situation, 0 otherwise
};

#endif
